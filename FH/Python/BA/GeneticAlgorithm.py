from ProteinStructureEvaluator import ProteinStructureEvaluator
from ProteinStructureCreator import ProteinStructureCreator
from ProteinStructureOperator import ProteinStructureOperator
from ProteinStructureSolution import ProteinStructureSolution
import random as rng
import math

class GeneticAlgorithm:

    def __init__(self, iterations: int, population_size: int, group_size: int, probabilities=None):
        if probabilities is None:
            probabilities = [1] * 6
        self.__iterations = iterations
        self.__population_size = population_size
        self.__probabilities = probabilities
        self.__probability_counters = [0] * 6

    def __initialize(self, seq_aa: str):
        solutions = []
        for i in range(self.__population_size):
            solutions.append(ProteinStructureCreator.initialize(seq_aa))

        return solutions

    def __choose_operator(self):
        op_rng = rng.randint(0, sum(self.__probabilities))
        operator = None
        operator_index = 0
        while operator is None:
            thresh = sum(self.__probabilities[:operator_index + 1])
            if op_rng < thresh:
                operator = operator_index

        return operator

    def start(self, seq_aa):
        best_solution = None
        best_score = None

        solutions = self.__initialize(seq_aa)

        for iteration in range(self.__iterations):
            children = []
            scores = [ProteinStructureEvaluator.evaluate(solution) for solution in solutions]

            while len(children) < len(solutions):
                operator = self.__choose_operator()

                if operator < 2:    # recombination
                    index_rng = 
                    group = scores





