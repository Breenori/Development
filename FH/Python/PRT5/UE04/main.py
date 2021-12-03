import pyteomics.mgf as pymgf
import pyteomics.mass as pymass

def parse_database(path: str) -> dict:
    with open(path, 'r') as file_db:
        data = dict()
        for line in file_db.readlines():
            elements = line.strip().split(',')
            mass = float(elements[0])
            peptide = elements[1]
            if mass not in data.keys():
                data[mass] = list()
            data[mass].append(peptide)

        return data


spectra = pymgf.read("spectraMS2.mgf")
header = pymgf.read_header("spectraMS2.mgf")
peptides_per_mass = parse_database("database.csv")
TOTAL_TOLERANCE = 0.02
PEAK_TOLERANCE = 0.04
PROTON_MASS = 1.007

test_weight = pymass.calculate_mass('AA')

#test = pymgf.MGF("spectraMS2.mgf", convert_arrays=0, read_charges=True, read_ions=True)

for spectrum in spectra:
    charge = float(str(spectrum['params']['charge'])[0])
    total_mass = spectrum['params']['pepmass'][0] * charge - PROTON_MASS * charge
    candidate_masses = [x for x in peptides_per_mass.keys()
                        if total_mass - TOTAL_TOLERANCE <= x <= total_mass + TOTAL_TOLERANCE]

    best_score = 0
    best_candidate = ""
    for candidate_mass in candidate_masses:
        for candidate in peptides_per_mass[candidate_mass]:
            cur_score = 0
            b_ions = list()
            y_ions = list()
            for i in range(1,len(candidate)+1):
                # pymass.calculate_mass returns the mass INCLUDING WATER --> subtract it for b ions only
                b_ions.append(pymass.calculate_mass(candidate[:i]) - 18 + PROTON_MASS)
                y_ions.append(pymass.calculate_mass(candidate[-i:]) + PROTON_MASS)

            for i in range(len(candidate)):
                cur_b_ion = b_ions[i]
                cur_y_ion = y_ions[i]
                b_peak_candidates = [x for x in spectrum['m/z array']
                                    if cur_b_ion - PEAK_TOLERANCE <= x <= cur_b_ion + PEAK_TOLERANCE]
                y_peak_candidates = [x for x in spectrum['m/z array']
                                        if cur_y_ion - PEAK_TOLERANCE <= x <= cur_y_ion + PEAK_TOLERANCE]
                if any(b_peak_candidates):
                    cur_score += len(b_peak_candidates)
                if any(y_peak_candidates):
                    cur_score += len(y_peak_candidates)

            cur_score = cur_score / (len(b_ions)+len(y_ions))
            if cur_score > best_score:
                best_score = cur_score
                best_candidate = candidate
    print(f"{round(best_score,4)}: {best_candidate}")