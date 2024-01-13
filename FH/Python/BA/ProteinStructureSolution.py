import math
import numpy as np
import matplotlib.pyplot as plt

class ProteinStructureSolution:

    def __init__(self, seq_hp: str, structure_cartesian: list, structure_directions: list):
        self.seq_HP = seq_hp
        self.structure_cartesian = structure_cartesian
        self.structure_directions = structure_directions

        self.hp_dict = dict()
        for i, pos in enumerate(structure_cartesian):
            self.hp_dict[pos] = seq_hp[i]

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
        ax.scatter(hxs, hys, hzs, color='red')
        ax.scatter(pxs, pys, pzs, color='blue')
        ax.plot(xs, ys, zs, color='black')
        plt.show()


