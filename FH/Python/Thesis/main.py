import numpy as np
from ProteinStructureCreator import ProteinStructureCreator
from ProteinStructureSolution import ProteinStructureSolution
from ProteinStructureOperator import ProteinStructureOperator
from GeneticAlgorithm import GeneticAlgorithm
from Superimposer import Superimposer



# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    seq = "TTCCPSIVARSNFNVCRLPGTPEALCATYTGCIIIPGATCPGDYAN"
    ga = GeneticAlgorithm(1, 500, 4)
    psso = ga.start(seq)

    Superimposer.superimpose("3nir", psso.structure_cartesian, seq)


