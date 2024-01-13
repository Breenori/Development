__author__ = "Sebastian Pritz"
__email__ = "s1910458022@students.fh-hagenberg.at"
"""
Description: This script assists with the mapping of iedb and pdb files.
- Input: IEDB assay CSV-File
- Output: Infofile of mapped entries, PDB/CIF files
"""

import csv
import gzip
import zipfile
import os
import re
import urllib.request
from multiprocessing import Pool as ThreadPool

PDBDIR = 'PDB//'
LOWER_BOUND = 9
UPPER_BOUND = 25

# Extracts relevant sequences and their IC50 statistics from the specified CSV.
def get_assay_entries(assay_filename):
    entries = dict()
    assay_filename_noext = '.'.join(assay_filename.split('.')[:-1])
    original_ext = assay_filename.split('.')[-1]
    cache_name = assay_filename_noext +"_"+str(LOWER_BOUND)+'-'+str(UPPER_BOUND) + '.cache'

    if not os.path.exists(assay_filename):
        print(assay_filename + ": specified file could not be found.")
        return []

    # if assay file is a zip, unzip it first
    if original_ext=='zip':
        with zipfile.ZipFile(assay_filename, 'r') as zip_ref:
            zip_ref.extractall('.')
            assay_filename = assay_filename_noext+'.csv'

    if not os.path.exists(cache_name):
        num_lines = 0

        with open(assay_filename, "r", encoding='utf-8') as iedb_file:
            # skip first two lines
            line = iedb_file.readline()
            line = iedb_file.readline()
            linecount = iedb_file

            csvreader = csv.reader(iedb_file, delimiter=',', quotechar='"')

            for row in csvreader:
                num_lines += 1
                seq = row[11]

                if len(seq) >= LOWER_BOUND and len(seq) <= UPPER_BOUND:
                    tmp = list()
                    tmp.append(row[70])  # qualitative measure
                    tmp.append(row[72])  # quantitative measure
                    tmp.append(row[69])  # units
                    tmp.append(row[67])  # method

                    # append data to dictionary entry
                    if seq not in entries.keys():
                        entries[seq] = list()
                    entries[seq].append(tmp)

        # after processing of the file, cache the relevant entries
        with open(cache_name, 'w') as seq_file:
            for entry in entries.keys():
                for subentry in entries[entry]:
                    seq_file.write(entry + ',' + ','.join(subentry) + '\n')
    else:
        # if cache file exists, read the data from it instead
        with open(cache_name) as seq_file:
            for line in seq_file.readlines():
                data = line.split(',')
                if data[0] not in entries.keys():
                    entries[data[0]] = list()
                tmp = list()
                tmp.append(data[1])
                tmp.append(data[2])
                tmp.append(data[3])
                tmp.append(data[4])
                entries[data[0]].append(tmp)

    # if assays were zipped, delete the extracted content to save data
    if original_ext == 'zip':
        if os.path.exists(assay_filename):
            os.remove(assay_filename)

    return entries

# Maps all IEDB-Entries to PDB based on the given entries and CSV.
def map_to_pdb(entries, seqres_filename):
    mapped_infos = dict()
    pdb_ids = set()

    if not os.path.exists(seqres_filename):
        print(seqres_filename + ": specified file could not be found.")
        return []

    # open and decode
    with gzip.open(seqres_filename, mode='rt', encoding='UTF-8') as seqres_file:
        acc_number = ''
        skipper = False

        for line in seqres_file.readlines():
            line = line.strip()
            matches = re.match('^>([^_]+).*mol:protein.*length:(\d+)\s+(.*)$', line)
            if skipper == False and line[0] != '>':

                found = False
                found_seq = ''
                for entry_seq in entries.keys():
                    if entry_seq in line:
                        found = True
                        found_seq = entry_seq
                        break

                if found:
                    pdb_ids.add(acc_number)
                    if acc_number not in mapped_infos.keys():
                        mapped_infos[acc_number] = list()
                    mapped_infos[acc_number].append(line)
                    mapped_infos[acc_number].append(entries[found_seq])

            # if line is header and length not within bounds, skip the next line
            elif line[0] == '>' and matches:
                length = int(matches.group(2))
                acc_number = matches.group(1)
                if length < LOWER_BOUND or length > UPPER_BOUND:
                    skipper = True
                else:
                    skipper = False

    # after mapping the files, write the combined infos to the filesystem
    with open('mapped_info.txt', 'w') as info_file:
        for pdbId in mapped_infos.keys():
            info_file.write('>' + pdbId + ',' + mapped_infos[pdbId][0] + ',' + str(len(mapped_infos[pdbId][1])) + '\n')
            for subentry in mapped_infos[pdbId][1]:
                info_file.write(','.join(subentry) + '\n')
            info_file.write('\n')

    return pdb_ids

# Downloads all PDB files using the given list.
def download_pdb(pdb_id):
    # If file already exists, skip the download.
    base_url = 'http://files.rcsb.org/download/'
    if not os.path.exists(PDBDIR + pdb_id + '.pdb') and not os.path.exists(PDBDIR + pdb_id + '.cif'):
        print("Downloading "+base_url+pdb_id)
        try:  # try .pdb
            urllib.request.urlretrieve(base_url + pdb_id + '.pdb', PDBDIR + pdb_id + '.pdb')
        except Exception:
            try:  # if pdb couldnt be found, try .cif
                urllib.request.urlretrieve(base_url + pdb_id + '.cif', PDBDIR + pdb_id + '.cif')
            except Exception:
                print(pdb_id + ' has no .pdb or .cif file available for download.')
    else:
        print("Skipping "+pdb_id)

def download_pdbs(pdb_ids):
    if not os.path.exists(PDBDIR):
        os.mkdir(PDBDIR)

    # alternative version using bash-script. Downloads all files as .pdbs AND .cifs. --> twice the data.
    '''
    with open('list_file.txt', 'w') as listFile:
        listFile.write(','.join(pdb_ids))

    if os.path.exists('list_file.txt'):
        os.system('batch_download.sh -f list_file.txt -p -c -o PDB')
    '''

    # version 2 without threads
    '''
    for pdb_id in pdb_ids:
        # If file already exists, skip the download.
        if not os.path.exists(PDBDIR + pdb_id + '.pdb'):
            print("Downloading " + pdb_id)
            try:  # try .pdb
                urllib.request.urlretrieve('http://files.rcsb.org/download/' + pdb_id + '.pdb',
                                           PDBDIR + pdb_id + '.pdb')
            except Exception:
                try:  # if pdb couldnt be found, try .cif
                    urllib.request.urlretrieve('http://files.rcsb.org/download/' + pdb_id + '.cif',
                                               PDBDIR + pdb_id + '.cif')
                except Exception:
                    print(pdb_id + ' has no .pdb or .cif file available for download.')'''

    # version 3 with threads
    pool = ThreadPool(4)
    results = pool.map(download_pdb, pdb_ids)

if __name__ == '__main__':
    iedb_entries = get_assay_entries('mhc_ligand_table_export_1615816328.zip')
    print("Finished extracting IEDB data.")

    print("Now mapping IEDB to PDB. This could take a while...")
    pdb_ids = map_to_pdb(iedb_entries, 'pdb_seqres.txt.gz')
    print(str(len(pdb_ids)) + " PDB IDs were successfully mapped to " + str(len(iedb_entries)) + " IEDB assay entries.")
    print("Inspect mapped_info.txt for more details.\n")

    ans = input("Do you also want to download all mapped PDB files? (y/n)")
    if ans.lower() in ['y','yes']:
        download_pdbs(pdb_ids)
