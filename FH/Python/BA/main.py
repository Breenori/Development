import numpy as np
import ProteinStructureCreator as psc
from ProteinStructureSolution import ProteinStructureSolution
from ProteinStructureEvaluator import ProteinStructureEvaluator
from ProteinStructureOperator import ProteinStructureOperator
from GeneticAlgorithm import GeneticAlgorithm




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    #psps = psc.ProteinStructureCreator.create_structure(psc.ProteinStructureCreator._get_hp_string("FSGPPGLQGRLQRLLQASGNHAAGILTM"), [1, 3, 5, 6, 10, 10, 6, 4, 4, 3, 8, 4, 9, 11, 2, 8, 11, 10, 3, 7, 5, 6, 10, 7, 4, 6, 7])
    psps1 = psc.ProteinStructureCreator.create_structure(psc.ProteinStructureCreator._get_hp_string("FSGPMCYFSGPMCY"), [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
    # psps2 = psc.ProteinStructureCreator.create_structure(psc.ProteinStructureCreator._get_hp_string("FSGPMCY"), [2, 2, 2, 2, 2, 2])
    #psps = psc.ProteinStructureCreator.initialize("FSGPPGLQGRLQRLLQASGNHAAGILTM")

    #psps, _ = ProteinStructureOperator.crossover_multipoint(psps1, psps2, 1)
    psps = ProteinStructureOperator.mutation_segment(psps1)
    score = ProteinStructureEvaluator.evaluate(psps)

    psps.show_3d()

    ga = GeneticAlgorithm(1000, 500, 4)
    ga.start("FSGPMCYFSGPMCYAALGYPTRACVLIM")


