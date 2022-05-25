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
    


def create_random_structure(seq_hp: str) -> ProteinStructureSolution:
    seq_coords = []

    seq_coords, seq_dir = create_random_structure_non(seq_hp)

    return ProteinStructureSolution(seq_hp,
                                    seq_coords,
                                    seq_dir)


    seq_coords, seq_dir, _ = create_random_structure_worker(seq_coords,
                                                            (0, 0, 0),
                                                            len(seq_hp))

    return ProteinStructureSolution(seq_hp,
                                    seq_coords,
                                    seq_dir)

def create_random_structure_non(seq_hp: str) -> (list, list):
    seq_coords = [(0, 0, 0)]
    seq_dir = []
       
    possibilities = []
    while len(seq_coords) < len(seq_hp):
        if len(possibilities) < len(seq_dir)+1:
            cur_possibilities = [i for i,dir in enumerate(get_directions_12()) if tuple(map(operator.add, seq_coords[-1], dir)) not in seq_coords]
            possibilities.append(cur_possibilities)
        if len(possibilities[-1]) == 0:
            del possibilities[-1]
            del seq_coords[-1]
            del seq_dir[-1]

        if len(possibilities[-1]) > 0:
            move = rng.randint(0, len(possibilities[-1])-1)
            seq_dir.append(move)
            seq_coords.append(tuple(map(operator.add, seq_coords[-1], get_directions_12()[possibilities[-1][move]])))
            del possibilities[-1][move]

    return seq_coords, seq_dir

def create_structure_non(seq_dir: str) -> (list, list):
    seq_coords = [(0, 0, 0)]
       
    possibilities = []
    tried = [False] * len(seq_dir)
    current_dir = 0
    while len(seq_coords) < len(seq_dir)+1:
        if len(possibilities) < len(seq_coords):
            cur_possibilities = [i for i,dir in enumerate(get_directions_12()) if tuple(map(operator.add, seq_coords[-1], dir)) not in seq_coords]
            possibilities.append(cur_possibilities)
        if len(possibilities[-1]) == 0:
            del possibilities[-1]
            del seq_coords[-1]
            current_dir = len(seq_coords)-1

        move = -1
        if current_dir > len(tried):
            print("hi")
        if not tried[current_dir]:
            move = possibilities.index(seq_dir[current_dir]) if seq_dir[current_dir] in possibilities else -1
            tried[current_dir] = True
     
        if move == -1:
            if len(possibilities[-1]) > 0:
                move = rng.randint(0, len(possibilities[-1])-1)
                seq_dir[current_dir] = move

        if len(possibilities[-1]) > 0:
            if tuple(map(operator.add, seq_coords[-1], get_directions_12()[possibilities[-1][move]])) not in seq_coords:
                seq_coords.append(tuple(map(operator.add, seq_coords[-1], get_directions_12()[possibilities[-1][move]])))
                if move < len(possibilities[-1]):
                    del possibilities[-1][move]
                current_dir = len(seq_coords)-1
            
            

    return seq_coords, seq_dir

def create_random_structure_worker(seq_coords: list,
                                    next_coord: (int, int, int),
                                    desired_length: int) -> (list, list, bool):
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
                    seq_dir: list,
                    parent1: ProteinStructureSolution = None,
                    parent2: ProteinStructureSolution = None) -> ProteinStructureSolution:

    structure_cartesian, structure_directions = create_structure_non(seq_dir)
    return ProteinStructureSolution(seq_hp,
                                    structure_cartesian,
                                    structure_directions,
                                    parent1,
                                    parent2)

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


def create_structure_worker(seq_dir: list,
                                seq_coords: list,
                                index: int,
                                next_coord: (int, int, int)) -> (list, list, bool):
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