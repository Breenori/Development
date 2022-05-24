import copy
import random as rng
import operator
from ProteinStructureSolution import ProteinStructureSolution
from ProteinStructureSettings import get_directions_12, get_hydrophobic



def get_hp_string(seq_aa: str):
    return "".join(["H" if aa in get_hydrophobic() else "P" for aa in seq_aa])


def initialize(seq_aa: str):
    seq_hp = get_hp_string(seq_aa)
    return create_random_structure(seq_hp)
    


def create_random_structure(seq_hp: str) -> tuple[list, list]:
    seq_coords = []
    seq_coords, seq_dir, _ = create_random_structure_worker(seq_coords,
                                                            (0, 0, 0),
                                                            len(seq_hp))

    return ProteinStructureSolution(seq_hp,
                                    seq_coords,
                                    seq_dir)

    return seq_coords, seq_dir


def create_random_structure_worker(seq_coords: list[tuple[int, int, int]],
                                    next_coord: tuple[int, int, int],
                                    desired_length: int):
    # try to append next 3d coordinate
    if next_coord not in seq_coords:
        seq_coords.append(next_coord)
    else:
        return seq_coords, [], False

    # if enough 3D coordinates have been generated, end recursion
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
        # try out possibile directions in random order and recurse
        while len(possibilities) > 0 and not valid:
            move = rng.randint(0, len(possibilities) - 1)

            ret_seq_coords, ret_seq_dir, valid = create_random_structure_worker(seq_coords,
                                                                                possibilities[move],
                                                                                desired_length)

            ret_seq_dir.insert(0, dict_dir[tuple(possibilities[move])])
            del possibilities[move]

        return ret_seq_coords, ret_seq_dir, valid


def create_structure(seq_hp: str,
                    seq_dir: list[int],
                    parent1: ProteinStructureSolution = None,
                    parent2: ProteinStructureSolution = None) -> ProteinStructureSolution:

    seq_coords = []
    structure_cartesian, structure_directions, valid = create_structure_worker(seq_dir,
                                                                                seq_coords,
                                                                                0,
                                                                                (0, 0, 0))

    return ProteinStructureSolution(seq_hp,
                                    structure_cartesian,
                                    structure_directions,
                                    parent1,
                                    parent2)


def create_structure_worker(seq_dir: list[int],
                                seq_coords: list[tuple[int, int, int]],
                                index: int,
                                next_coord: tuple[int, int, int]):
    # if next coord is valid, add it to the list
    if next_coord not in seq_coords:
        seq_coords.append(next_coord)

    # if there are more coordinates than directions the algorithm is finished.
    if len(seq_coords) == len(seq_dir) + 1:
        return seq_coords, seq_dir, True
    else:
        # try to extend in the supplied direction
        direction_idx = seq_dir[index]
        next_point = tuple(map(operator.add, seq_coords[-1], get_directions_12()[direction_idx]))
        valid = next_point not in seq_coords

        # if possible, extend
        if valid:
            return create_structure_worker(seq_dir,
                                                                        seq_coords,
                                                                        index + 1,
                                                                        next_point)
        # else, try out all possibilities:
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
            # try all 12 directions. if none are possible, go back one recursion step.
            while len(possibilities) > 0 and not valid:
                move = rng.randint(0, len(possibilities) - 1)
                ret_seq_directions[index] = dict_dir[tuple(possibilities[move])]
                ret_seq_coords, ret_seq_directions, valid = create_structure_worker(seq_dir,
                                                seq_coords,
                                                index + 1,
                                                possibilities[move])
                del possibilities[move]

            return ret_seq_coords, ret_seq_directions, valid