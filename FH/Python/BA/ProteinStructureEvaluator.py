from ProteinStructureSolution import ProteinStructureSolution
import operator

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

class ProteinStructureEvaluator:

    @staticmethod
    def evaluate(solution: ProteinStructureSolution):
        pairs = set()

        for i, pos in enumerate(solution.structure_cartesian):
            if solution.hp_dict[pos] == "H":
                possibilities = [tuple(map(operator.add, pos, cur_dir)) for cur_dir in directions]

                if i > 0:
                    possibilities.remove(solution.structure_cartesian[i-1])
                if i < len(solution.structure_cartesian)-1:
                    possibilities.remove(solution.structure_cartesian[i+1])

                possibilities = set([x for x in possibilities
                                     if x in solution.hp_dict.keys() and solution.hp_dict[x] == "H"])

                for possibility in possibilities:
                    if possibility in solution.structure_cartesian \
                    and (possibility, solution.structure_cartesian[i]) not in pairs:
                            pairs.add((possibility, solution.structure_cartesian[i]))
                            pairs.add((solution.structure_cartesian[i], possibility))

        return len(pairs)/2