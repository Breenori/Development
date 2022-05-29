def get_3to1():
    return {'CYS': 'C', 'ASP': 'D', 'SER': 'S', 'GLN': 'Q', 'LYS': 'K',
            'ILE': 'I', 'PRO': 'P', 'THR': 'T', 'PHE': 'F', 'ASN': 'N', 
            'GLY': 'G', 'HIS': 'H', 'LEU': 'L', 'ARG': 'R', 'TRP': 'W', 
            'ALA': 'A', 'VAL': 'V', 'GLU': 'E', 'TYR': 'Y', 'MET': 'M'}


def get_directions_12():
    return [
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


def get_hydrophobic():
    return ['G', 'A', 'P', 'V', 'L', 'I', 'M', 'F', 'Y', 'W']


def get_polar():
    return ['S', 'T', 'C', 'N', 'Q', 'D', 'E', 'K', 'H', 'R']
