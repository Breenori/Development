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


    def __select_random_from_group(self):
        pass

    def __tournament_selection(self, solutions: list, scores: list, k: int):
        selection = []
        while len(selection) < len(solutions):
            idx_groupstart = rng.randint(0, len(solutions)-k-1)
            group_solutions = solutions[idx_groupstart, idx_groupstart+k]
            group_scores = scores[idx_groupstart, idx_groupstart+k]
            max_score = max(group_scores)

            candidates = [group_solutions[y] for y,x in enumerate(group_scores) if x == max_score]

            selection.append(candidates[0,rng.randint(0, len(candidates)-1)])






    def start(self, seq_aa: str):
        best_solution = None
        best_score = None

        solutions = self.__initialize(seq_aa)

        for iteration in range(self.__iterations):
            rng.shuffle(solutions)
            scores = [ProteinStructureEvaluator.evaluate(solution) for solution in solutions]

            selected_parents = self.__tournament_selection(solutions, scores, 5)





