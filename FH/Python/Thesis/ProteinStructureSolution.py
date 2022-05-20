import math
import numpy as np
import operator
import matplotlib.pyplot as plt
from ProteinStructureSettings import get_directions_12


class ProteinStructureSolution:

    def __init__(self,
                 structure_hp: str,
                 structure_cartesian: list,
                 structure_directions: list,
                 parent1=None,
                 parent2=None):
        self.seq_HP = structure_hp
        self.structure_cartesian = structure_cartesian
        self.structure_directions = structure_directions

        self.hp_dict = dict()
        for i, pos in enumerate(structure_cartesian):
            self.hp_dict[pos] = structure_hp[i]

        self.op_self = -1
        self.parent1 = parent1
        self.parent2 = parent2
        self.score = 0

    def __str__(self):
        return ", ".join([str(x) for x in self.structure_directions])

    def __repr__(self):
        return ", ".join([str(x) for x in self.structure_directions])

    def set_creation_operator(self, op_self: int):
        self.op_self = op_self

    def show_3d(self):
        fig = plt.figure(figsize=(4, 4))

        xs = [x[0] for x in self.structure_cartesian]
        ys = [x[1] for x in self.structure_cartesian]
        zs = [x[2] for x in self.structure_cartesian]

        hxs = [x for i, x in enumerate(xs) if self.seq_HP[i] == 'H']
        hys = [y for i, y in enumerate(ys) if self.seq_HP[i] == 'H']
        hzs = [z for i, z in enumerate(zs) if self.seq_HP[i] == 'H']

        pxs = [x for i, x in enumerate(xs) if self.seq_HP[i] == 'P']
        pys = [y for i, y in enumerate(ys) if self.seq_HP[i] == 'P']
        pzs = [z for i, z in enumerate(zs) if self.seq_HP[i] == 'P']


        ax = fig.add_subplot(111, projection='3d')
        ax.set_title('Score '+str(self.score))
        ax.scatter(hxs, hys, hzs, color='red')
        ax.scatter(pxs, pys, pzs, color='blue')
        ax.plot(xs, ys, zs, color='black')
        plt.show()

    def evaluate(self):
        pairs = set()

        for i, pos in enumerate(self.structure_cartesian):
            if self.hp_dict[pos] == "H":
                possibilities = [tuple(map(operator.add, pos, cur_dir)) for cur_dir in get_directions_12()]

                if i > 0 and self.structure_cartesian[i-1] in possibilities:
                    possibilities.remove(self.structure_cartesian[i-1])
                if i < len(self.structure_cartesian)-2 and self.structure_cartesian[i+1] in possibilities:
                    possibilities.remove(self.structure_cartesian[i+1])

                possibilities = set([x for x in possibilities
                                     if x in self.hp_dict.keys() and self.hp_dict[x] == "H"])

                for possibility in possibilities:
                    if possibility in self.structure_cartesian \
                    and (possibility, self.structure_cartesian[i]) not in pairs:
                            pairs.add((possibility, self.structure_cartesian[i]))
                            pairs.add((self.structure_cartesian[i], possibility))

        self.score = -len(pairs)/2
