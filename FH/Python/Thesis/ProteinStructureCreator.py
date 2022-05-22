import copy
import random as rng
import operator
from ProteinStructureSolution import ProteinStructureSolution
from ProteinStructureSettings import get_directions_12, get_hydrophobic, get_polar


class ProteinStructureCreator:

    def __init__(self):
        pass

    @staticmethod
    def __get_hp_string(seq_aa: str):
        return "".join(["H" if aa in get_hydrophobic() else "P" for aa in seq_aa])

    @staticmethod
    def initialize(seq_aa: str):

        seq_hp = ProteinStructureCreator.__get_hp_string(seq_aa)
        return ProteinStructureCreator.__create_random_structure(seq_hp)
        

    @staticmethod
    def __create_random_structure(seq_hp: list) -> (list, list):
        seq_coords = []

        #return  ProteinStructureCreator.__create_random_structure_non(seq_hp)

        seq_coords, seq_dir, _ = ProteinStructureCreator.__create_random_structure_worker(seq_coords,
                                                                                          (0, 0, 0),
                                                                                          len(seq_hp))

        return ProteinStructureSolution(seq_hp,
                                        seq_coords,
                                        seq_dir)

        return seq_coords, seq_dir

    @staticmethod
    def __create_random_structure_worker(seq_coords: list,
                                         next_coord: (int, int, int),
                                         desired_length: int):
        if next_coord not in seq_coords:
            seq_coords.append(next_coord)
        else:
            return seq_coords, [], False

        if len(seq_coords) == desired_length:
            return seq_coords, [], True
        else:
            valid = False
            possibilities = [tuple(map(operator.add, seq_coords[-1], cur_direction)) for cur_direction in get_directions_12()]
            dict_dir = dict()
            for direction, coord in enumerate(possibilities):
                dict_dir[tuple(coord)] = direction
            possibilities = list(set(possibilities) - set(seq_coords))

            ret_seq_coords = []
            ret_seq_dir = []
            while len(possibilities) > 0 and not valid:
                move = rng.randint(0, len(possibilities) - 1)

                ret_seq_coords, ret_seq_dir, valid = ProteinStructureCreator \
                    .__create_random_structure_worker(seq_coords,
                                                      possibilities[
                                                          move],
                                                      desired_length)

                ret_seq_dir.insert(0, dict_dir[tuple(possibilities[move])])
                del possibilities[move]

            return ret_seq_coords, ret_seq_dir, valid

    @staticmethod
    def create_structure(seq_hp: str,
                         seq_dir: list,
                         parent1: ProteinStructureSolution = None,
                         parent2: ProteinStructureSolution = None) -> ProteinStructureSolution:

        #return ProteinStructureCreator.__create_structure_non(seq_hp, seq_dir, parent1, parent2)
        seq_coords = []

        structure_cartesian, structure_directions, valid = ProteinStructureCreator.__create_structure_worker(seq_dir,
                                                                                                             seq_coords,
                                                                                                             0,
                                                                                                             (0, 0, 0))

        return ProteinStructureSolution(seq_hp,
                                        structure_cartesian,
                                        structure_directions,
                                        parent1,
                                        parent2)

    @staticmethod
    def __create_structure_worker(seq_dir: list,
                                  seq_coords: list,
                                  index: int,
                                  next_coord: (int, int, int)):
        if next_coord not in seq_coords:
            seq_coords.append(next_coord)

        if len(seq_coords) == len(seq_dir) + 1:
            return seq_coords, seq_dir, True
        else:
            direction_idx = seq_dir[index]
            next_point = tuple(map(operator.add, seq_coords[-1], get_directions_12()[direction_idx]))
            valid = next_point not in seq_coords

            if valid:
                return ProteinStructureCreator.__create_structure_worker(seq_dir,
                                                                         seq_coords,
                                                                         index + 1,
                                                                         next_point)
            else:
                possibilities = [tuple(map(operator.add, seq_coords[-1], cur_direction))
                                 for cur_direction in get_directions_12()]
                dict_dir = dict()
                for direction, coord in enumerate(possibilities):
                    dict_dir[tuple(coord)] = direction
                possibilities = list(set(possibilities) - set(seq_coords))

                ret_seq_coords = []
                ret_seq_directions = copy.deepcopy(seq_dir)
                valid = False
                while len(possibilities) > 0 and not valid:
                    move = rng.randint(0, len(possibilities) - 1)
                    ret_seq_directions[index] = dict_dir[tuple(possibilities[move])]
                    ret_seq_coords, ret_seq_directions, valid = ProteinStructureCreator \
                        .__create_structure_worker(seq_dir,
                                                   seq_coords,
                                                   index + 1,
                                                   possibilities[move])
                    del possibilities[move]

                return ret_seq_coords, ret_seq_directions, valid

    @staticmethod
    def __create_structure_non(seq_hp: str,
                         seq_dir: list,
                         parent1: ProteinStructureSolution = None,
                         parent2: ProteinStructureSolution = None) -> ProteinStructureSolution:
        seq_coords = [(0,0,0)]
        valid = True
        cur_index = 0
        while len(seq_coords) < len(seq_hp) and valid:
            direction_idx = seq_dir[cur_index]
            next_point = tuple(map(operator.add, seq_coords[-1], get_directions_12()[direction_idx]))
            valid_point = next_point not in seq_coords

            if valid_point:
                seq_coords.append(next_point)
            else:
                possibilities = [tuple(map(operator.add, seq_coords[-1], cur_direction))
                                 for cur_direction in get_directions_12()]
                dict_dir = dict()
                for direction, coord in enumerate(possibilities):
                    dict_dir[tuple(coord)] = direction
                possibilities = list(set(possibilities) - set(seq_coords))

                found = False
                while len(possibilities) > 0 and not found:
                    move = rng.randint(0, len(possibilities) - 1)
                    if possibilities[move] not in seq_coords:
                        seq_coords.append(next_point)
                        seq_dir[cur_index] = dict_dir[tuple(possibilities[move])]
                        found = True
                    del possibilities[move]
                
                if not found:
                    valid = False
                    print("invalid structure")

        return ProteinStructureSolution(seq_hp, seq_coords, seq_dir, parent1, parent2)

    @staticmethod
    def __create_random_structure_non(seq_hp: str) -> ProteinStructureSolution:
        seq_coords = [(0,0,0)]
        seq_dir = []
        valid = True
 
        while len(seq_coords) < len(seq_hp) and valid:
            direction_idx = rng.randint(0,len(get_directions_12())-1)
            next_point = tuple(map(operator.add, seq_coords[-1], get_directions_12()[direction_idx]))
            valid_point = next_point not in seq_coords

            if valid_point:
                seq_coords.append(next_point)
                seq_dir.append(direction_idx)
            else:
                possibilities = [tuple(map(operator.add, seq_coords[-1], cur_direction))
                                 for cur_direction in get_directions_12()]
                dict_dir = dict()
                for direction, coord in enumerate(possibilities):
                    dict_dir[tuple(coord)] = direction
                possibilities = list(set(possibilities) - set(seq_coords))

                found = False
                while len(possibilities) > 0 and not found:
                    move = rng.randint(0, len(possibilities) - 1)
                    if possibilities[move] not in seq_coords:
                        seq_coords.append(next_point)
                        seq_dir.append(dict_dir[tuple(possibilities[move])])
                        found = True
                    del possibilities[move]
                
                if not found:
                    valid = False

        return ProteinStructureSolution(seq_hp, seq_coords, seq_dir, None, None)