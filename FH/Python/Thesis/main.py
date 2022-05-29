import requests
import time
import Bio.PDB
import os.path
import os
import re
import numpy as np
from GeneticAlgorithm import GeneticAlgorithm
from ProteinStructureSettings import get_3to1
from Superimposer import Superimposer

import warnings
import sys
warnings.filterwarnings("ignore")
sys.setrecursionlimit(2000)

def evaluate_casp(filename: str, iterations: int, population_size: int, out_name: str):
    # write csv header
    with open(out_name, 'w') as out_csv:
        out_csv.write("pdb_id;len;time;energy;rmsd\n")

    # parse targets
    with open(filename, 'r') as target_csv:
        target_csv.readline()
        pdb_set = set()
        for line in target_csv.readlines():
            line = line.replace("\n","").strip()
            # find PDB id
            result = re.search(r"\s(\w{4})\s*$", line)

            last_field = line.split(";")[-1]
            # if target was not canceled and PDB id found
            if "canceled" not in last_field.lower() and result:
                pdb_id = result.group(1)
                if pdb_id not in pdb_set:
                    pdb_set.add(pdb_id)
                    evaluate_for_pdb(pdb_id, iterations, population_size, out_name)


def evaluate_for_pdb(pdb_id: str, iterations: int, population_size: int, out_name: str):
    #try:
    # fetch .pdb file from PDB
    if not os.path.exists(f'pdbs/{pdb_id}.pdb'):
        open(f"pdbs/{pdb_id}.pdb",'wb').write(requests.get(pdb_url_pdb+pdb_id+".pdb").content)

    structure = Bio.PDB.PDBParser().get_structure(pdb_id, f"pdbs/{pdb_id}.pdb")
    if len(structure) == 0:
        with open(out_name, 'a') as out_csv:
            out_csv.write(f"{pdb_id};-;DNF;inf\n")
        return None
    ref_model = structure[0]

    # build seq from PDB
    seq = ""
    for ref_chain in ref_model:
        seq += "".join([Bio.PDB.Polypeptide.three_to_one(ref_res.resname) for ref_res in ref_chain if ref_res.resname in get_3to1().keys()])
    
    if len(seq) <= 1000:
        # execute GA and measure time
        start = time.time()
        ga = GeneticAlgorithm(iterations, population_size, 4, 5, 100)
        psso = ga.start(seq)
        end = time.time()

        # superimpose and calculate RMSD
        rmsd = Superimposer.superimpose(pdb_id, psso.structure_cartesian, seq)

        # write result to file
        with open(out_name, 'a') as out_csv:
            out_csv.write(f"{pdb_id};{len(seq)};{round(end-start,2)};{psso.score};{round(rmsd,2)}\n")
        print(end-start, "seconds")
        return rmsd
    else:
        print("Structure too long. Length:",len(seq))
    #except Exception as e:
        # on error, log failure
        #print(pdb_id, "failed")
        #print(e)
        #with open(out_name, 'a') as out_csv:
        #    out_csv.write(f"{pdb_id};-;DNF;inf\n")
        #return None
        

def evaluate_results(csv_path: str):
    with open(csv_path, 'r') as csv_in:
        # get all RMSD values from file and calculate metrics
        csv_in.readline()
        rmsd_list = list()
        for line in csv_in.readlines():
            elements = line.split(';')
            if elements[2] != 'DNF':
                rmsd = elements[4].replace("\n","")
                if rmsd != "inf":
                    rmsd_list.append(float(rmsd))

        print(np.average(rmsd_list))
        print(np.min(rmsd_list))
        print(np.max(rmsd_list))


if not os.path.exists('aligned_pdbs'):
    os.mkdir('aligned_pdbs')
if not os.path.exists('pdbs'):
    os.mkdir('pdbs')

if __name__ == '__main__':
    pdb_url_pdb = "https://files.rcsb.org/download/"

    evaluate_casp("targetlist.csv", 10, 250, "output_10_elite5.csv")
    evaluate_for_pdb("6t1z",100,250,'output_6tiz_random.csv')
    evaluate_results("output_10_elite5.csv")
