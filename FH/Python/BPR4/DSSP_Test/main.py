from Bio.PDB import PDBParser
from Bio.PDB.DSSP import DSSP
from Bio import BiopythonWarning
import warnings
warnings.simplefilter('ignore', BiopythonWarning)


p = PDBParser()
structure = p.get_structure("1AI0", "1ai0.pdb")
model = structure[0]
#dssp = DSSP(model, "1ai0.pdb", dssp='mkdssp')
print(model)