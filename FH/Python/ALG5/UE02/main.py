import numpy as np
import math

def read_hmms(path: str) -> list[dict]:
    hmm_list = list()
    valid = True

    with open(path, 'r') as file_hmm:
        hmm = dict()
        for line in file_hmm.readlines():
            if len(line.strip()) == 0 and len(hmm.keys())>0:
                for idx in range(hmm['num_states']):
                    sum_states = hmm['sta_dist'][idx].sum()
                    sum_r_observations = 1  # hmm['obs_dist'][idx].sum()
                    sum_c_observations = hmm['obs_dist'][:, idx].sum()

                    if sum_states < 1.0 or sum_c_observations < 1.0 or sum_r_observations < 1.0:
                        valid = False

                if valid:
                    hmm_list.append(hmm)
                hmm = dict()
                valid = True
                continue

            elements = line.strip().split('\t')
            elements[0] = elements[0].upper()
            if elements[0] == 'STATES':
                states = elements[1:]
                hmm['num_states'] = len(states)
                hmm['states'] = dict(zip(states,list(range(len(states)))))
                hmm['sta_dist'] = np.zeros((len(states), len(states)), float)
            elif elements[0] == 'OBSERVATIONS':
                observations = elements[1:]
                hmm['num_observations'] = len(observations)
                hmm['observations'] = dict(zip(observations,list(range(len(observations)))))
                hmm['obs_dist'] = np.zeros((len(observations), len(observations)), float)
            elif elements[0] == 'START_DIST':
                if len(elements) != hmm['num_states']+1:
                    print(f"Error reading start probabilities: expected {hmm['num_states']} got {len(elements)-1}")
                    valid = False
                hmm['start_dist'] = [float(x) for x in elements[1:]]
            elif elements[0] == 'STA_DIST':
                if len(elements) != hmm['num_states']+2:
                    print(f"Error reading state probability matrix: expected {hmm['num_states']} columns, got {len(elements)-2} ")
                    valid = False
                hmm['sta_dist'][int(elements[1])][:] = [float(x) for x in elements[2:]]
            elif elements[0] == 'OBS_DIST':
                if len(elements) != hmm['num_observations']+2:
                    print(f"Error reading observation probability matrix: expected {hmm['num_observations']} columns, got {len(elements)-2} ")
                    return dict()
                hmm['obs_dist'][int(elements[1])][:] = [float(x) for x in elements[2:]]

        if len(hmm.keys())>0:
            hmm_list.append(hmm)

    return hmm_list

def read_observations(path: str, mapping: dict) -> list:
    all_observations = list()
    with open(path, 'r') as file_obs:
        for line in file_obs.readlines():
            elements = line.strip().split(',')
            observations = [int(x) if isinstance(x, str) and x.isdigit() else mapping[x] for x in elements]
            all_observations.append(observations)

    return all_observations

def forward_algorithm(obs: list, hmm: dict) -> float:
    probs = list()
    for state_idx in range(hmm['num_states']):
        cur_prob = hmm['start_dist'][state_idx] * hmm['obs_dist'][obs[0]][state_idx]
        probs.append(cur_prob)

    return sum(forward_worker(obs, 1, probs, hmm))

def forward_worker(obs: list, obs_index: int, prev: list, hmm: dict) -> list:
    if obs_index < len(obs):
        probs = list()
        for new_state_idx in range(hmm['num_states']):
            p_obs_state = hmm['obs_dist'][obs[obs_index]][new_state_idx]
            prev_sum = 0
            for prev_state_idx in range(hmm['num_states']):
                prev_sum += prev[prev_state_idx] * hmm['sta_dist'][prev_state_idx][new_state_idx]
            probs.append(p_obs_state * prev_sum)

        return forward_worker(obs, obs_index+1, probs, hmm)
    else:
        return prev



hmm_list = read_hmms('hmm1.hmm')
observations = read_observations('observation.txt', hmm_list[0]['observations'])
prob = forward_algorithm(observations[0], hmm_list[0])
print(prob)
print(math.log(prob))
observations = read_observations('observation.txt', hmm_list[1]['observations'])
prob = forward_algorithm(observations[0], hmm_list[1])
print(prob)
print(math.log(prob))