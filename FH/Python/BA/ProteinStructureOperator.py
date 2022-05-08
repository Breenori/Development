import random as rng
import math
import copy
from ProteinStructureSolution import ProteinStructureSolution
from ProteinStructureCreator import ProteinStructureCreator
from ProteinStructureEvaluator import ProteinStructureEvaluator

directions = [
    [1, 1, 0],
    [-1, -1, 0],
    [-1, 1, 0],
    [1, -1, 0],
    [0, 1, 1],
    [0, 1, -1],
    [1, 0, 1],
    [1, 0, -1],
    [0, -1, 1],
    [-1, 0, 1],
    [0, -1, -1],
    [-1, 0, -1],
]


class ProteinStructureOperator:

    @staticmethod
    def crossover_single(parent1: ProteinStructureSolution, parent2: ProteinStructureSolution):
        return ProteinStructureOperator.crossover_multipoint(parent1, parent2, 1)

    @staticmethod
    def crossover_multipoint(parent1: ProteinStructureSolution, parent2: ProteinStructureSolution, n: int):
        points = []
        max_segment_length = math.floor(len(parent1.structure_directions) / n)

        if max_segment_length <= 2:
            print("Amount of crossover points too high. Applying correction.")
            n = math.floor(len(parent1.structure_directions) / 3)
            max_segment_length = math.floor(len(parent1.structure_directions) / n)

        for i in range(0, n):
            points.append(rng.randint(i * max_segment_length + 1, (i + 1) * max_segment_length - 1))

        seq1_directions = parent1.structure_directions[0:points[0]]
        seq2_directions = parent2.structure_directions[0:points[0]]
        for i in range(0, n - 1):
            part1 = parent1.structure_directions[points[i]:points[i + 1]]
            part2 = parent2.structure_directions[points[i]:points[i + 1]]
            seq1_directions += part2 if i % 2 == 0 else part1
            seq2_directions += part1 if i % 2 == 0 else part2

        part1 = parent1.structure_directions[points[-1]:]
        part2 = parent2.structure_directions[points[-1]:]
        seq1_directions += part1 if n % 2 == 0 else part2
        seq2_directions += part2 if n % 2 == 0 else part1

        return ProteinStructureCreator.create_structure(parent1.seq_HP, seq1_directions), \
               ProteinStructureCreator.create_structure(parent2.seq_HP, seq2_directions)

    @staticmethod
    def mutation_segment(parent: ProteinStructureSolution):
        num_mutations = rng.randint(2, 7)
        if num_mutations > len(parent.structure_directions):
            num_mutations = len(parent.structure_directions)

        pos = rng.randint(0, len(parent.structure_directions) - num_mutations)

        seq_directions = copy.deepcopy(parent.structure_directions)
        for i in range(pos, pos + num_mutations):
            seq_directions[i] = rng.randint(0, len(directions))

        return ProteinStructureCreator.create_structure(parent.seq_HP, seq_directions)

    @staticmethod
    def mutation_exhaustive_search(parent: ProteinStructureSolution):
        mutation_pos = rng.randint(0, len(parent.structure_directions))

        best_score = None
        best_solution = None
        for direction in directions:
            if direction != parent.structure_directions[mutation_pos]:
                seq_dir = copy.deepcopy(parent.structure_directions)
                seq_dir[mutation_pos] = direction
                cur_solution = ProteinStructureCreator.create_structure(parent.seq_HP, seq_dir)
                cur_score = ProteinStructureEvaluator.evaluate(cur_solution)
                if best_score is None or best_score > cur_score:
                    best_score = cur_score
                    best_solution = [cur_solution]
                elif best_score == cur_score:
                    best_solution.append(cur_solution)

        return best_solution[rng.randint(0, len(best_solution))]

    @staticmethod
    def mutation_local_move(parent: ProteinStructureSolution):
        mutation_pos = rng.randint(0, len(parent.structure_directions)-1)

        seq_dir = copy.deepcopy(parent.structure_directions)
        seq_dir[mutation_pos], seq_dir[mutation_pos+1] = seq_dir[mutation_pos+1], seq_dir[mutation_pos]

        return ProteinStructureCreator.create_structure(parent.seq_HP, seq_dir)

    @staticmethod
    def mutation_loop_move(parent: ProteinStructureSolution):
        offset = rng.randint(2, 5)
        mutation_pos = rng.randint(0, len(parent.structure_directions) - offset)

        seq_dir = copy.deepcopy(parent.structure_directions)
        seq_dir[mutation_pos], seq_dir[mutation_pos + offset] = seq_dir[mutation_pos + offset], seq_dir[mutation_pos]

        return ProteinStructureCreator.create_structure(parent.seq_HP, seq_dir)





