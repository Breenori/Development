import numpy as np
from enum import Enum


# Enum for human readable pathing
class Dir(Enum):
    NONE = 0
    UP = 1
    LEFT = 2
    DIAGONAL = 3


class SubstitutionMatrix:
    def __init__(self, matrix, indexer):
        self.__matrix = matrix
        self.__indexer = indexer

    # get scoring for given AA pair
    def get(self, aa1, aa2):
        if aa1 not in self.__indexer.keys():
            print(f"Error: Invalid residue {aa1}.")
            exit(-1)
        elif aa2 not in self.__indexer.keys():
            print(f"Error: Invalid residue {aa2}.")
            exit(-1)

        return self.__matrix[self.__indexer[aa1], self.__indexer[aa2]]


def readSubstitutionMatrix(fileName: str, delimiter=',') -> SubstitutionMatrix:
    with open(fileName, 'r') as inputFile:
        # read header (which residues)
        AAs = inputFile.readline().strip().split(delimiter)
        # create a dictionary to map the residues with their indices
        indexer = dict(zip(AAs, range(0,len(AAs))))

        # create a numpy array.
        # read every line and convert values to integer
        subMat = np.zeros((len(AAs),len(AAs)), np.int16)
        for i, line in enumerate(inputFile.readlines()):
            line = line.strip()
            odds = line.split(delimiter)[1:]
            odds = [int(x) for x in odds]
            subMat[i, :] = odds[:]

        # use array and dictionary to create SubstitutionMatrix class
        return SubstitutionMatrix(subMat, indexer)


def getSequenceAlignment(seq1: str, seq2: str, subMatrix: SubstitutionMatrix, gapCost: int = 8, isGlobal: bool = True, overlapAllowed: bool = False) -> (str, str, int):
    if len(seq1)==0 or len(seq2)==0:
        print("One of the sequences contains no residues. Exiting.")
        exit(-1)

    # Initialize matrix: one for scoring, one for pathing
    alignmentMat = np.zeros((len(seq1)+1, len(seq2)+1), np.int16)
    directionMat = np.ones((len(seq1)+1, len(seq2)+1), Dir)
    # set value for unvisited fields to minimum of int16 (about -32000)
    alignmentMat[:] = np.iinfo(np.int16).min
    # left upper corner is always zero
    alignmentMat[0,0] = 0
    # in the beginning there are no paths
    directionMat[:] = Dir.NONE

    # Initialization of first column (overlap: 0, else: increasing gap cost), Path always UP
    for row in range(1, len(seq1)+1):
        alignmentMat[row, 0] = 0 if overlapAllowed else row * -gapCost
        directionMat[row, 0] = Dir.UP

    # Initialization of first row (overlap: 0, else: increasing gap cost), Path always LEFT
    for col in range(1, len(seq2)+1):
        alignmentMat[0, col] = 0 if overlapAllowed else col * -gapCost
        directionMat[0, col] = Dir.LEFT

    # Calculate the entire matrix row-by-row so there is always a left, upper, and diagonal element
    for row in range(1, len(seq1)+1):
        for col in range(1, len(seq2)+1):
            # calculate scores
            diagScore = alignmentMat[row-1, col-1] + subMatrix.get(seq1[row-1], seq2[col-1])
            yScore = alignmentMat[row-1, col] - gapCost
            xScore = alignmentMat[row, col-1] - gapCost

            # search the max score and set the current fields score and pathing accordingly
            if diagScore >= yScore and diagScore >= xScore:
                alignmentMat[row, col] = diagScore if isGlobal or diagScore > 0 else 0
                directionMat[row, col] = Dir.DIAGONAL
            elif xScore >= diagScore and xScore >= yScore:
                alignmentMat[row, col] = xScore if isGlobal or xScore > 0 else 0
                directionMat[row, col] = Dir.LEFT
            elif yScore >= diagScore and yScore >= xScore:
                alignmentMat[row, col] = yScore if isGlobal or yScore > 0 else 0
                directionMat[row, col] = Dir.UP

    # depending on the settings, find the starting point for backtracing
    if isGlobal:
        # For global and overlap, find the maximum value in the last row/column
        if overlapAllowed:
            rowMax = np.max(alignmentMat[-1, :])
            colMax = np.max(alignmentMat[:, -1])

            if rowMax >= colMax:
                seq1pos = len(seq1)
                seq2pos = np.unravel_index(np.argmax(alignmentMat[-1, :]), alignmentMat[-1, :].shape)[0]
            else:
                seq1pos = np.unravel_index(np.argmax(alignmentMat[:, -1]), alignmentMat[:, -1].shape)[0]
                seq2pos = len(seq2)
        # for global without overlaps, it is always the bottom right cell
        else:
            seq1pos = len(seq1)
            seq2pos = len(seq2)
    # for local alignments the cell with the highest score is used
    else:
        (seq1pos, seq2pos) = np.unravel_index(np.argmax(alignmentMat), alignmentMat.shape)

    # read the score from the calculated field
    score = alignmentMat[seq1pos, seq2pos]


    seq1aligned = ""
    seq2aligned = ""
    # backtrace from the last field to calculate the aligned sequences
    while (isGlobal and not overlapAllowed and (seq1pos > 0 or seq2pos > 0))\
            or (isGlobal and overlapAllowed and (seq1pos > 0 and seq2pos > 0))\
            or (not isGlobal and alignmentMat[seq1pos, seq2pos] != 0):

        # if going diagonal, go both directions and add residues from both sequences
        if directionMat[seq1pos, seq2pos] == Dir.DIAGONAL:
            seq1aligned = seq1[seq1pos-1] + seq1aligned
            seq2aligned = seq2[seq2pos-1] + seq2aligned
            seq1pos -= 1
            seq2pos -= 1
        # if going left, only go forward with seq2, add its residue and make a gap in sequence 1
        # (I mistakenly made sequence 1 horizontally, doesn't make a difference in calculation)
        elif directionMat[seq1pos, seq2pos] == Dir.LEFT:
            seq1aligned = "-" + seq1aligned
            seq2aligned = seq2[seq2pos-1] + seq2aligned
            seq2pos -= 1
        # if going up, only go forward with seq1, add its residue and make a gap in sequence 2
        elif directionMat[seq1pos, seq2pos] == Dir.UP:
            seq1aligned = seq1[seq1pos-1] + seq1aligned
            seq2aligned = "-" + seq2aligned
            seq1pos -= 1

    # for overlapping alignments, add back the overlaps
    if overlapAllowed:
        if seq1pos > 0:
            seq1aligned = seq1[0:seq1pos] +seq1aligned
            seq2aligned = "-" * seq1pos + seq2aligned
        elif seq2pos > 0:
            seq2aligned = seq2[0:seq2pos] + seq2aligned
            seq1aligned = "-" * seq2pos + seq1aligned

        if len(seq1aligned) < len(seq1):
            seq1aligned += seq1[len(seq1aligned)-1:]
        elif len(seq2aligned) < len(seq2):
            seq2aligned += seq2[len(seq2aligned)-1:]

        if len(seq1aligned) < len(seq2aligned):
            seq1aligned += "-" * (len(seq2aligned) - len(seq1aligned))
        elif len(seq2aligned) < len(seq1aligned):
            seq2aligned += "-" * (len(seq1aligned) - len(seq2aligned))


    return seq1aligned, seq2aligned, score


testSeq1 = "HEAGAWGHEE"
testSeq2 = "PAWHEAE"
#testSeq2 = "GGGGGPAWHEAEGGGGGGGGGGGGG"
#testSeq2 = "GARLICBUTTER"


subMat = readSubstitutionMatrix("BLOSUM62.csv")
(a1, a2, score) = getSequenceAlignment(testSeq1, testSeq2, subMat, 3, True, False)
print(f"Score: {score}\n{a1}\n{a2}")
