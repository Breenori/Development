import numpy as np
from UE04_alignment import SubstitutionMatrix, readSubstitutionMatrix, getSequenceAlignment
import time


def build_wordlist(seq, subMat):
    amino_acids = ['A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V']

    # split all words
    initial_words = list()
    for i in range(0, len(seq)-(w-1)):
        initial_words.append(seq[i:i+w])

    # generate all possible words with single point mutations
    words = dict()
    for i, word in enumerate(initial_words):
        word_l = list(word)
        for pos in range(0,w-1):
            for aa in amino_acids:
                word_l[pos] = aa
                mutated_word = "".join(word_l)

                _, _, score = getSequenceAlignment(word, mutated_word, subMat)
                if score >= T and mutated_word:
                    if mutated_word not in words.keys():
                        words[mutated_word] = list()
                    if i not in words[mutated_word]:
                        words[mutated_word].append(i)

    # add initial words that had too low of a score (exact matches)
    for i, word in enumerate(initial_words):
        if word not in words.keys():
            words[word] = list()
            words[word].append(i)
        elif word in words.keys() and i not in words[word]:
            words[word].append(i)

    return words


def read_fasta(filenames):
    fasta_dict = dict()
    for filename in filenames:
        with open(filename, 'r') as file_in:
            title = ""
            seq = ""
            for line in file_in.readlines():
                line = line.strip()
                if line.startswith(">"):
                    if len(seq)>0 and len(title)>0 and seq.isalpha():
                        fasta_dict[title] = seq
                    title = line[1:]
                    seq = ""
                else:
                    seq += line

            if len(seq) > 0 and len(title) > 0 and seq.isalpha():
                fasta_dict[title] = seq

    return fasta_dict


def blastp(search_seq, database, w, T, subMat, debug=False):
    words = build_wordlist(search_seq, subMat)

    best_score = -np.inf
    best_entry = ""
    best_offset = 0

    for entry_key in database:
        entry = database[entry_key]
        for i in range(0, len(entry) - (w - 1)):
            current_word = entry[i:i + w]
            if current_word in words.keys():
                for offset in words[current_word]:
                    offset_start = 0
                    offset_end = 0

                    _, _, score = getSequenceAlignment(search_seq[offset - offset_start:offset + w + offset_end],
                                                       entry[i - offset_start:i + w + offset_end],
                                                       subMat)
                    changed = True
                    while (score > T / 2 and changed):
                        _, _, score = getSequenceAlignment(search_seq[offset - offset_start:offset + w + offset_end],
                                                           entry[i - offset_start:i + w + offset_end],
                                                           subMat)
                        changed = False
                        if i - offset_start > 0 and offset - offset_start > 0:
                            offset_start += 1
                            changed = True
                        if offset + w + offset_end < len(search_seq) - 1 and i + w + offset_end < len(entry) - 1:
                            offset_end += 1
                            changed = True

                        if debug:
                            print(search_seq[offset - offset_start:offset + w + offset_end])
                            print(entry[i - offset_start:i + w + offset_end])
                            print("<-<-<-<-<-<-<-<-<-<-<-<-")
                        if score > best_score:
                            best_score = score
                            best_entry = entry_key
                            best_offset = i - offset_start - (offset - offset_start)
                    if debug:
                        print("-------------------------------------")

    return best_entry, best_score, best_offset


w = 5
T = 30
search_seq = "AVKTCITVPVSGIEVREITTCY"
#search_seq = "GILTMIHVPVSAVEVREITTCY"
#search_seq = "CHILDRENOFBODOM"

subMat = readSubstitutionMatrix("PAM250.csv", ',')
inputs = ["MYOGLOBIN.txt"]
database = read_fasta(inputs)

start = time.time()
title, score, offset = blastp(search_seq, database, w, T, subMat)
end = time.time()

if title != "":
    print(f"Execution-time: {end-start}")
    T_len = len(database[title])

    print(f"Best match: {title}")
    print(f"Score: {score}")
    print(f"Offset: {offset}")
    print(f"T: {min(0,offset)*'-'}{database[title][max(0,offset):max(0,offset)+len(search_seq)]}")
    print(f"S: {search_seq}")
else:
    print(f"Blast could not be executed. Try changing parameters...")