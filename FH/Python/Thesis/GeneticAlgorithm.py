from ProteinStructureCreator import ProteinStructureCreator
from ProteinStructureOperator import ProteinStructureOperator
from ProteinStructureSolution import ProteinStructureSolution
from concurrent.futures import ThreadPoolExecutor
import random as rng
import numpy as np
import math


class GeneticAlgorithm:

    def __init__(self, iterations: int, population_size: int, group_size: int, probabilities=None, probability_change=None):
        if probabilities is None:
            probabilities = [1] * 6
            probabilities[0] = 5
            probabilities[1] = 5
        self.__iterations = iterations
        self.__population_size = population_size
        self.__probabilities = probabilities
        self.__probability_counters = [0] * 6
        if probability_change is None:
            self.__probability_change = 0.1
        else:
            self.__probability_change = probability_change

    def __initialize(self, seq_aa: str):
        solutions = []
        for i in range(self.__population_size):
            solutions.append(ProteinStructureCreator.initialize(seq_aa))
            solutions[-1].evaluate()

        return solutions

    def __choose_operator(self, recombination_allowed: bool):
        op_rng = rng.randint(0 if recombination_allowed else int(self.__probabilities[0]*100000+self.__probabilities[1]*100000), int(sum(self.__probabilities) * 100000))/100000.0
        operator = None
        operator_index = 0
        while operator is None:
            thresh = sum(self.__probabilities[:operator_index + 1])
            if op_rng <= thresh:
                operator = operator_index
            operator_index += 1

        return operator

    def __tournament_selection(self, solutions: list,  k: int) -> list:
        selection = []
        while len(selection) < len(solutions):
            idx_groupstart = rng.randint(0, len(solutions) - k - 1)
            group_solutions = solutions[idx_groupstart:idx_groupstart + k]
            group_scores = [sol.score for sol in group_solutions]
            min_score = min(group_scores)
            if min_score < 1:
                candidates = [group_solutions[index] for index, value in enumerate(group_scores) if value == min_score]

                selection.append(candidates[rng.randint(0, len(candidates)) - 1])

        return selection

    def __create_child_generation(self, selected_parents, seq_len, best_score) -> list:
        children = []
        while len(children) < self.__population_size:
            operator = self.__choose_operator(len(selected_parents) - len(children) > 1)
            if operator < 2:  # recombination
                child1 = None
                child2 = None
                if operator == 0:
                    child1, child2 = ProteinStructureOperator.crossover_single(selected_parents[len(children)-1],
                                                                               selected_parents[len(children)])

                elif operator == 1:
                    child1, child2 = ProteinStructureOperator.crossover_multipoint(selected_parents[len(children)-1],
                                                                                   selected_parents[len(children)],
                                                                                   rng.randint(1, math.floor(
                                                                                       seq_len / 5)))

                child1.set_creation_operator(operator)
                child2.set_creation_operator(operator)
                child1.evaluate()
                child2.evaluate()

                child_score = max(child1.score, child2.score)
                impact = (best_score - child_score)

                if child_score < best_score:
                    self.__probabilities[operator] += self.__probability_change * impact
                    self.__probabilities[child1.parent1.op_self] += (self.__probability_change / 4) * impact
                    self.__probabilities[child1.parent2.op_self] += (self.__probability_change / 4) * impact
                    self.__probability_counters[operator] = 0
                else:
                    self.__probability_counters[operator] += 1
                    if self.__probability_counters[operator] >= 1000:
                        self.__probabilities[operator] /= 2
                        self.__probability_counters[operator] = 0

                children.append(child1)
                children.append(child2)
            else:  # mutation operators
                child = None
                if operator == 2:
                    child = ProteinStructureOperator.mutation_segment(selected_parents[len(children)])
                elif operator == 3:
                    child = ProteinStructureOperator.mutation_exhaustive_search(selected_parents[len(children)])
                elif operator == 4:
                    child = ProteinStructureOperator.mutation_local_move(selected_parents[len(children)])
                else:
                    child = ProteinStructureOperator.mutation_loop_move(selected_parents[len(children)])

                child.evaluate()

                if child.score > best_score:
                    self.__probability_counters[operator] += 1
                    if self.__probability_counters[operator] == 1000:
                        self.__probabilities[operator] /= 2
                        self.__probability_counters[operator] = 0
                else:
                    improvement = (best_score - child.score)
                    if operator == 3:
                        improvement /= 12.0
                    self.__probabilities[operator] += self.__probability_change * improvement
                    self.__probabilities[child.parent1.op_self] += (self.__probability_change / 2) * improvement
                    self.__probability_counters[operator] = 0

                children.append(child)
        return children

    def start(self, seq_aa: str) -> ProteinStructureSolution:
        best_solution = None
        best_score = 0

        solutions = self.__initialize(seq_aa)
        for solution in solutions:
            solution.evaluate()

        scores = [sol.score for sol in solutions]
        max_index = np.argmin(scores)
        best_solution = solutions[max_index]
        best_score = scores[max_index]


        converge_counter = 100
        for iteration in range(self.__iterations):
            print("Iteration",iteration)
            print("best", best_score)
            print([round(x/sum(self.__probabilities),2) for x in self.__probabilities])
            rng.shuffle(solutions)
            selected_parents = self.__tournament_selection(solutions, 4)

            children = self.__create_child_generation(selected_parents, len(seq_aa), best_score)

            # crowding
            """
            for i, child in enumerate(children):
                randnum = rng.randint(1,100)
                if (randnum <= 2):
                    DMEs = []
                    for parent in solutions:
                        DMEs.append(child.calc_DME(parent))
                    similar = np.argmax(DMEs)
                    if solutions[similar].score < child.score:
                        children[i] = solutions[similar]
                    elif solutions[similar].score == child.score:
                        randnum = rng.randint(0,1)
                        if randnum == 1:
                            children[i] = solutions[similar]
            """

            solutions = children
            scores = [sol.score for sol in solutions]
            max_index = np.argmin(scores)

            if best_score is None or scores[max_index] < best_score:
                best_solution = solutions[max_index]
                best_score = scores[max_index]
                converge_counter = 100
            else:
                converge_counter -= 1

            if converge_counter == 0:
                break
        # best_solution.show_3d()
        return best_solution




