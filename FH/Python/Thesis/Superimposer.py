import Bio.PDB
import Bio.PDB.Residue
import numpy
import math

class Superimposer:

    @staticmethod
    def superimpose(pdb_code: str, atoms_pred: list, seq_alt: str):
        d3to1 = {'CYS': 'C', 'ASP': 'D', 'SER': 'S', 'GLN': 'Q', 'LYS': 'K',
                    'ILE': 'I', 'PRO': 'P', 'THR': 'T', 'PHE': 'F', 'ASN': 'N', 
                    'GLY': 'G', 'HIS': 'H', 'LEU': 'L', 'ARG': 'R', 'TRP': 'W', 
                    'ALA': 'A', 'VAL':'V', 'GLU': 'E', 'TYR': 'Y', 'MET': 'M'}

        atoms_pred = [numpy.array(atom).astype(numpy.float32) for atom in atoms_pred]
        pdb_filename = "pdbs/%s.pdb" % pdb_code
        pdb_out_filename = "aligned_pdbs/%s_aligned.pdb" % pdb_code

        structure = Bio.PDB.PDBParser().get_structure(pdb_code, pdb_filename)
        ref_model = structure[0]
        test = ref_model.get_atoms()

        len_seq = len(seq_alt)
        atoms_ref = []
        for model in structure:
            
            for ref_chain in model:
               atoms_ref= [ref_res['CA'] for ref_res in ref_chain if ref_res.resname in d3to1.keys()]

        ref_mean_dist = numpy.average([math.sqrt((atoms_ref[i+1].coord[0] - atoms_ref[i].coord[0])**2 + (atoms_ref[i+1].coord[1] - atoms_ref[i].coord[1])**2 + (atoms_ref[i+1].coord[2] - atoms_ref[i].coord[2])**2) for i in range(0, len(atoms_ref)-1)])

        bio_atoms_pred = []
        for i in range(len(atoms_pred)):
            atoms_pred[i][0] *= ref_mean_dist
            atoms_pred[i][1] *= ref_mean_dist
            atoms_pred[i][2] *= ref_mean_dist
            cur_atom = Bio.PDB.Atom.Atom('CA', atoms_pred[i], 2, 1.0, ' ', ' CA ', 'C')  
            bio_atoms_pred.append(cur_atom)

        # Align these paired atom lists:
        super_imposer = Bio.PDB.Superimposer()
        super_imposer.set_atoms(atoms_ref, bio_atoms_pred)

        # Update the structure by moving all the atoms in
        # this model (not just the ones used for the alignment)
        super_imposer.apply(bio_atoms_pred)

        print("RMS(pdb, prediction) = %0.2f" % (super_imposer.rms))
        io = Bio.PDB.PDBIO()
        io.set_structure(structure)
        io.save(pdb_out_filename)

        return super_imposer.rms


