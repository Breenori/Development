import numpy as np
import math
import random

# define fields that valid hmms need to populate
OBLIGATORY_FIELDS = ['num_states',
                     'num_observations',
                     'states',
                     'observations',
                     'start_dist',
                     'sta_dist',
                     'obs_dist']
EPSILON = 0.00001


def check_hmm(hmm: dict, hmm_index: int) -> bool:
    # check if hmm contains all necessary keys
    if all(field in hmm.keys() for field in OBLIGATORY_FIELDS):
        valid = True
        # check if hmm is valid = matrix row/column sums need to equal 1
        for idx in range(hmm['num_states']):
            sum_states = hmm['sta_dist'][idx].sum()

            # sums should be 1 (corrected by floating point errors)
            if not(1.0 - EPSILON < sum_states < 1.0 + EPSILON):
                print(f"Error: probabilities for state {idx} in HMM{hmm_index} don't sum up to 1.0.")
                valid = False
                break

        for idx in range(hmm['num_states']):
            sum_observations = hmm['obs_dist'][:, idx].sum()

            if not(1.0 - EPSILON < sum_observations < 1.0 + EPSILON):
                print(f"Error: probabilities for observation {idx} in HMM{hmm_index} don't sum up to 1.0.")
                valid = False
                break
    else:
        valid = False
    return valid


def read_hmms(path: str) -> list:
    hmm_list = list()
    valid = True

    with open(path, 'r') as file_hmm:
        hmm = dict()
        hmm_index = 0
        for line in file_hmm.readlines():
            # if hmm exists and empty line occurs, try to add it
            if len(line.strip()) == 0:
                # only if the HMM is valid, add it to the list.
                if valid and check_hmm(hmm, hmm_index):
                    hmm_list.append(hmm)
                # in every case, reset the hmm dict and valid flag
                hmm = dict()
                valid = True
                hmm_index += 1
                continue
            elif valid:
                # split the tab separated line into its elements
                elements = line.strip().split('\t')
                elements[0] = elements[0].upper()
                # STATES keyword occurs: save the amount, create a dict for indexing and initialize the state change matrix
                if elements[0] == 'STATES':
                    states = elements[1:]
                    hmm['num_states'] = len(states)
                    hmm['states'] = dict(zip(states,list(range(len(states)))))
                    hmm['sta_dist'] = np.zeros((len(states), len(states)), float)
                # OBSERVATION keyword occurs: same as for states, but for observations
                elif elements[0] == 'OBSERVATIONS':
                    observations = elements[1:]
                    hmm['num_observations'] = len(observations)
                    hmm['observations'] = dict(zip(observations,list(range(len(observations)))))
                    hmm['obs_dist'] = np.zeros((len(observations), len(states)), float)
                # START_DIST keyword occurs: check for right amount and read in the initial probabilities of each state
                elif elements[0] == 'START_DIST':
                    if len(elements) != hmm['num_states']+1:
                        print(f"Error reading start probabilities in HMM{hmm_index}: expected {hmm['num_states']} got {len(elements)-1}")
                        valid = False
                    elif len(elements) == hmm['num_states']+1:
                        hmm['start_dist'] = [float(x) for x in elements[1:]]
                        if not(1.0-EPSILON < sum(hmm['start_dist']) < 1.0+EPSILON):
                            print(f"Error: start distributions in HMM{hmm_index} don't sum up to 1.0")
                            valid = False
                # STA_DIST keyword occurs: check for right amount of values
                # and initialize the designated row of the state change probability matrix (a)
                elif elements[0] == 'STA_DIST':
                    if len(elements) != hmm['num_states']+2:
                        print(f"Error reading state probability matrix in HMM{hmm_index}: expected {hmm['num_states']} columns, got {len(elements)-2} ")
                        valid = False
                    elif len(elements) == hmm['num_states']+2:
                        hmm['sta_dist'][int(elements[1])][:] = [float(x) for x in elements[2:]]
                # OBS_DIST keyword occurs: similar to STA_DIST, check for right amount of values
                # and initialize the state probabilities for the given observation
                elif elements[0] == 'OBS_DIST':
                    if len(elements) != hmm['num_states']+2:
                        print(f"Error reading observation probability matrix in HMM{hmm_index}: expected {hmm['num_observations']} columns, got {len(elements)-2} ")
                        valid = False
                    elif len(elements) == hmm['num_states']+2:
                        hmm['obs_dist'][int(elements[1])][:] = [float(x) for x in elements[2:]]

        # if file ends without empty line, but hmm is filled/Valid
        if valid and check_hmm(hmm, hmm_index):
            hmm_list.append(hmm)

    return hmm_list


def read_observations(path: str, mapping: dict) -> list:
    all_observations = list()
    with open(path, 'r') as file_obs:
        # read through all lines: each line is one set of observations
        for line in file_obs.readlines():
            valid = True
            elements = line.strip().split(',')
            for i in range(len(elements)):
                if elements[i] in mapping.keys():
                    elements[i] = mapping[elements[i]]
                elif elements[i].isdigit():
                    elements[i] = int(elements[i])
                    if elements[i] not in mapping.values():
                        valid = False
                else:
                    valid = False

                if not valid:
                    print(f"Invalid observation: '{elements[i]}'")
                    break

            if valid:
                all_observations.append(elements)
            valid = True

    return all_observations


def forward_algorithm(obs: list, hmm: dict) -> float:
    probs = list()

    # populate list by calculating initial probabilities of states based on first observation
    for state_idx in range(hmm['num_states']):
        cur_prob = hmm['start_dist'][state_idx] * hmm['obs_dist'][obs[0]][state_idx]
        probs.append(cur_prob)

    # start the recursion using the observations, observation index, current probabilities and the HMM
    return sum(forward_worker(obs, 1, probs, hmm))


def forward_worker(obs: list, obs_index: int, prev: list, hmm: dict) -> list:
    # if all indices have been calculated = stop condition
    while obs_index < len(obs):
        probs = list()
        # calculate new probabilities of states, depending on current index and previous probabilities
        for new_state_idx in range(hmm['num_states']):
            p_obs_state = hmm['obs_dist'][obs[obs_index]][new_state_idx]
            prev_sum = 0
            for prev_state_idx in range(hmm['num_states']):
                prev_sum += prev[prev_state_idx] * hmm['sta_dist'][prev_state_idx][new_state_idx]
            probs.append(p_obs_state * prev_sum)

        # next recursion step with index+1
        prev = probs #return forward_worker(obs, obs_index+1, probs, hmm)
        obs_index += 1
    else:
        return prev


def test_bad():
    print("Malformed files test:")
    # test wrong hmms and observations
    failed = read_hmms('bad.hmm')
    print(failed)


def test_dimensions():
    print("Different dimensions test:")
    # test differing dimensions
    other_dims = read_hmms('valid_other_dimensions.hmm')
    print(other_dims)
    rng_observation = list()
    for i in range(20):
        rng_observation.append(random.randint(0,2))

    for hmm_index, hmm in enumerate(other_dims):
        prob_other_dim = forward_algorithm(rng_observation, hmm)
        print(f"Probability for HMM{hmm_index}: {prob_other_dim}")
        print(f"Log likelihood for HMM{hmm_index}: {math.log10(prob_other_dim) if prob_other_dim != 0.0 else 0.0}")


def test_reference():
    print("Valid Test:")
    # test valid ones
    hmm_list = read_hmms('hmms.hmm')
    observations = read_observations('observations.txt', hmm_list[0]['observations'])

    # create a random long list of observations
    rng_observation = list()
    for i in range(500):
        rng_observation.append(random.randint(0,2))
    observations.append(rng_observation)
    print()

    # calculate results for each observations, for each hmm
    for idx_obs, observation in enumerate(observations):
        best_hmm = -1
        best_log = -np.inf
        for idx_hmm, hmm in enumerate(hmm_list):
            probability_of_hmm = forward_algorithm(observation, hmm)
            probability_log = math.log10(probability_of_hmm) if probability_of_hmm != 0.0 else 0.0
            print(f"Probability of HMM{idx_hmm} for observation {idx_obs}:\t\t {probability_of_hmm}")
            print(f"Log-Likelihood of HMM{idx_hmm} for observation {idx_obs}:\t {probability_log}")
            if probability_log != 0 and probability_log > best_log:
                best_log = probability_log
                best_hmm = idx_hmm
        print(f"The best HMM for observation {idx_obs} is:\tHMM{best_hmm}")
        print("-------------------------------------------------------------------------------------------------")


test_bad()
print("-------------------------------------------------------------")
print("-------------------------------------------------------------")
test_dimensions()
print("-------------------------------------------------------------")
print("-------------------------------------------------------------")
test_reference()