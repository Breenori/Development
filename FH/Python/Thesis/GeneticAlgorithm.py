from ProteinStructureCreator import initialize
from ProteinStructureOperator import crossover_two, crossover_multipoint, mutation_segment, mutation_exhaustive_search, mutation_local_move, mutation_loop_move
from ProteinStructureSolution import ProteinStructureSolution
import random as rng
import numpy as np
import math


class GeneticAlgorithm:

    def __init__(self, iterations: int,
                    population_size: int,
                    group_size: int,
                    convergence_limit: int,
                    probabilities: list=None,
                    probability_change: float=None):
        self.__iterations = iterations
        self.__population_size = population_size
        self.__group_size = group_size
        self.__convergence_limit = convergence_limit

        # initialize probabilities with 1 --> 1 / 1*6 = 0.16 = 16%
        if probabilities is None:
            probabilities = [1] * 6
            probabilities[0] = 5
            probabilities[1] = 5
        self.__probabilities = probabilities
        self.__probability_counters = [0] * 6
        if probability_change is None:
            probability_change = 1
        self.__probability_change = probability_change

    def __initialize(self, seq_aa: str):
        # create random solutions according to population size
        solutions = []
        for i in range(self.__population_size):
            solutions.append(initialize(seq_aa))
            solutions[-1].evaluate()

        return solutions

    def __choose_operator(self, recombination_allowed: bool):
        # randomly choose one of the 6 operators, corresponding to the probabilities
        op_rng = rng.randint(0 if recombination_allowed else int(self.__probabilities[0]*100+self.__probabilities[1]*100), int(sum(self.__probabilities) * 100))/100.0
        operator = None
        operator_index = 0
        while operator is None:
            thresh = sum(self.__probabilities[:operator_index + 1])
            if op_rng <= thresh:
                operator = operator_index
            operator_index += 1

        return operator

    def __tournament_selection(self, solutions: list) -> list:
        selection = []
        while len(selection) < len(solutions):
            idx_groupstart = rng.randint(0, len(solutions) - self.__group_size - 1)
            group_solutions = solutions[idx_groupstart:idx_groupstart + self.__group_size]
            group_scores = [sol.score for sol in group_solutions]
            min_score = min(group_scores)
            if min_score < 1:
                candidates = [group_solutions[index] for index, value in enumerate(group_scores) if value == min_score]

                selection.append(candidates[rng.randint(0, len(candidates)) - 1])

        return selection

    def __create_child_generation(self, selected_parents: list,
                                    seq_len: int, 
                                    best_score: int) -> list:
        children = []
        while len(children) < self.__population_size:
            operator = self.__choose_operator(len(selected_parents) - len(children) > 1)
            if operator < 2:  # recombination
                child1 = None
                child2 = None
                if operator == 0:
                    child1, child2 = crossover_two(selected_parents[len(children)-1],
                                                                               selected_parents[len(children)])

                elif operator == 1:
                    child1, child2 = crossover_multipoint(selected_parents[len(children)-1],
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
                    child = mutation_segment(selected_parents[len(children)])
                elif operator == 3:
                    child = mutation_exhaustive_search(selected_parents[len(children)])
                elif operator == 4:
                    child = mutation_local_move(selected_parents[len(children)])
                else:
                    child = mutation_loop_move(selected_parents[len(children)])

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

        # create random solutions
        solutions = self.__initialize(seq_aa)
        for solution in solutions:
            solution.evaluate()

        # initial evaluation
        scores = [sol.score for sol in solutions]
        max_index = np.argmin(scores)
        best_solution = solutions[max_index]
        best_score = scores[max_index]


        converge_counter = self.__convergence_limit
        # start iterating
        for iteration in range(self.__iterations):
            print("iteration",iteration)
            print("best solution", best_solution.score)
            # shuffle solutions and select parent generation
            rng.shuffle(solutions)
            selected_parents = self.__tournament_selection(solutions)

            # create child generation using recombination or mutation
            children = self.__create_child_generation(selected_parents, len(seq_aa), best_score)

            # child generation becomes new parent generation and is evaluated
            solutions = children
            scores = [sol.score for sol in solutions]
            max_index = np.argmin(scores)

            if best_score is None or scores[max_index] < best_score:
                best_solution = solutions[max_index]
                best_score = scores[max_index]
                converge_counter = self.__convergence_limit
            else:
                converge_counter -= 1

            if converge_counter == 0:
                break

        return best_solution