import requests
import time
import Bio.PDB
import os.path
import os
import re
import warnings
import sys
import numpy as np
from GeneticAlgorithm import GeneticAlgorithm
from Superimposer import Superimposer
warnings.filterwarnings("ignore")
sys.setrecursionlimit(4000)

def evaluate_casp(filename: str, iterations: int, population_size: int, out_name: str):
    with open(out_name, 'w') as out_csv:
        out_csv.write("pdb_id;len;time;rmsd\n")

    with open(filename, 'r') as target_csv:
        target_csv.readline()
        pdb_set = set()
        for line in target_csv.readlines():
            line = line.replace("\n","").strip()
            result = re.search(r"\s(\w{4})\s*$", line)

            last_field = line.split(";")[-1]
            if "canceled" not in last_field.lower() and result:
                pdb_id = result.group(1)
                if pdb_id not in pdb_set:
                    pdb_set.add(pdb_id)
                    evaluate_for_pdb(pdb_id, iterations, population_size, out_name)


def evaluate_for_pdb(pdb_id: str, iterations: int, population_size: int, out_name: str):
    try:
        open(f"pdbs/{pdb_id}.pdb",'wb').write(requests.get(pdb_url_pdb+pdb_id+".pdb").content)

        structure = Bio.PDB.PDBParser().get_structure(pdb_id, f"pdbs/{pdb_id}.pdb")
        ref_model = structure[0]

        seq = ""
        for model in structure:
            for ref_chain in model:
                seq = "".join([Bio.PDB.Polypeptide.three_to_one(ref_res.resname) for ref_res in ref_chain if ref_res.resname in d3to1.keys()])
            
        
        start = time.time()
        ga = GeneticAlgorithm(iterations, population_size, 4)
        psso = ga.start(seq)
        end = time.time()

        rmsd = Superimposer.superimpose(pdb_id, psso.structure_cartesian, seq)
        with open(out_name, 'a') as out_csv:
            out_csv.write(f"{pdb_id};{len(seq)};-;{rmsd}\n")
        #print(end-start, "seconds")
        return rmsd
    except:
        with open(out_name, 'a') as out_csv:
            out_csv.write(f"{pdb_id};-;DNF;inf\n")
        return None

def evaluate_results(csv_path: str):
    with open(csv_path, 'r') as csv_in:
        csv_in.readline()
        rmsd_list = list()
        for line in csv_in.readlines():
            elements = line.split(';')
            if elements[2] != 'DNF':
                rmsd = elements[3]
                rmsd_list.append(float(rmsd))

        print(np.average(rmsd_list))
        print(np.min(rmsd_list))
        print(np.max(rmsd_list))


if __name__ == '__main__':
    d3to1 = {'CYS': 'C', 'ASP': 'D', 'SER': 'S', 'GLN': 'Q', 'LYS': 'K',
            'ILE': 'I', 'PRO': 'P', 'THR': 'T', 'PHE': 'F', 'ASN': 'N', 
            'GLY': 'G', 'HIS': 'H', 'LEU': 'L', 'ARG': 'R', 'TRP': 'W', 
            'ALA': 'A', 'VAL':'V', 'GLU': 'E', 'TYR': 'Y', 'MET': 'M'}
    pdb_url_pdb = "https://files.rcsb.org/download/"

    if not os.path.exists('pdbs'):
        os.mkdir('pdb')
    if not os.path.exists('pdbs_aligned'):
        os.mkdir('pdbs_aligned')

    evaluate_casp("targetlist.csv", 0, 250, "output_1000.csv")
    #evaluate_results("output_1000.csv")


                    

