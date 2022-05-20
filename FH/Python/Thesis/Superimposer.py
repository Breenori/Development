import Bio.PDB
import numpy

class Superimposer:

    @staticmethod
    def superimpose(pdb_code: str, structure: list, seq: str):
        pdb_filename = "%s.pdb" % pdb_code
        pdb_out_filename = "%s_aligned.pdb" % pdb_code

        print("Loading PDB file %s" % pdb_filename)
        structure_pdb = Bio.PDB.PDBParser().get_structure(pdb_code, pdb_filename)

        print("Everything aligned to first model...")
        ref_model = structure_pdb[0]

        alt_atoms = structure
        for model in structure_pdb:
            ref_atoms = []
            for ref_chain in model:
                chain = [ref_res['CA'] for ref_res in ref_chain if ref_res ]
                print(chain)
            print(ref_atoms)



        # Align these paired atom lists:
        super_imposer = Bio.PDB.Superimposer()
        super_imposer.set_atoms(ref_atoms, alt_atoms)

        if ref_model.id == alt_model.id:
            # Check for self/self get zero RMS, zero translation
            # and identity matrix for the rotation.
            assert numpy.abs(super_imposer.rms) < 0.0000001
            assert numpy.max(numpy.abs(super_imposer.rotran[1])) < 0.000001
            assert numpy.max(numpy.abs(super_imposer.rotran[0]) - numpy.identity(3)) < 0.000001
        else:
            # Update the structure by moving all the atoms in
            # this model (not just the ones used for the alignment)
            super_imposer.apply(alt_model.get_atoms())

        print("RMS(first model, model %i) = %0.2f" % (alt_model.id, super_imposer.rms))

        print("Saving aligned structure as PDB file %s" % pdb_out_filename)
        io = Bio.PDB.PDBIO()
        io.set_structure(structure)
        io.save(pdb_out_filename)

        print("Done")


