#include "external_merge_sort.h"

void ExternalMergeSort::Sort(std::string const& FileToSort, size_t const NumValues){

	FileManipulator Manipulator;

	//setting file names
	FileManipulator::FileName F0 = "f0.txt";
	FileManipulator::FileName F1 = "f1.txt";
	FileManipulator::FileName G0 = "g0.txt";
	FileManipulator::FileName G1 = "g1.txt";

	//opening 8 streams
	std::ifstream InStreamF0{ F0 };
	std::ifstream InStreamG0{ G0 };
	std::ifstream InStreamF1{ F1 };
	std::ifstream InStreamG1{ G1 };

	std::ofstream OutStreamF0{ F0 };
	std::ofstream OutStreamG0{ G0 };
	std::ofstream OutStreamF1{ F1 };
	std::ofstream OutStreamG1{ G1 };

	//putting streams in vector
	std::vector<std::ifstream*> InStreamsVec{ &InStreamF0, &InStreamF1, &InStreamG0, &InStreamG1 };
	std::vector<std::ofstream*> OutStreamsVec{ &OutStreamF0,&OutStreamF1, &OutStreamG0, &OutStreamG1 };

	//split original file
	Manipulator.SplitFile(FileToSort, { F0, F1 });

	//setting stream situations
	size_t CurrentOutStreamSituation = 0;
	size_t CurrentStreamSituation = 0;

	//initializing current streams
	std::ifstream* CurrentFirstInStream = InStreamsVec[INSTREAMF0];
	std::ifstream* CurrentSecondInStream = InStreamsVec[INSTREAMF1];

	std::ofstream* CurrentOutStream = OutStreamsVec[OUTSTREAMG0];

	FileManipulator::ValueType Value;

	int RunLength = 1;
	int Counter = 0;
	
	//if one of input files is empty --> finished sorting
	while ((CurrentFirstInStream->peek() != EOF) || (CurrentSecondInStream->peek() != EOF)) {

		//read while files are not end
		while ((CurrentFirstInStream->peek() != EOF) && (CurrentSecondInStream->peek() != EOF)) {

			//getting input vecs
			std::vector<FileManipulator::ValueType> FirstInputVec;
			std::vector<FileManipulator::ValueType> SecondInputVec;

			//read while current run length is not reached
			while (Counter < RunLength) {

				//read in values from streams and save in vecs
				if (*CurrentFirstInStream >> Value) {

					FirstInputVec.push_back(Value);

				}

				if (*CurrentSecondInStream >> Value) {

					SecondInputVec.push_back(Value);

				}

				++Counter;
			}

			//initialize merged vecs size and merge input vectors
			std::vector<FileManipulator::ValueType> MergedVecs(FirstInputVec.size() + SecondInputVec.size());

			Merge(FirstInputVec, SecondInputVec, MergedVecs);

			//write merged vecs to current ouput file
			Manipulator.WriteOut(MergedVecs, *CurrentOutStream);
			//CurrentOutStream->close();

			//change output stream
			if (CurrentOutStreamSituation == 0 && CurrentStreamSituation == 0) {
				CurrentOutStream = OutStreamsVec[OUTSTREAMG1];
				++CurrentOutStreamSituation;
			}
			else if (CurrentOutStreamSituation == 1 && CurrentStreamSituation == 0) {
				CurrentOutStream = OutStreamsVec[OUTSTREAMG0];
				CurrentOutStreamSituation = 0;
			}
			else if (CurrentOutStreamSituation == 0 && CurrentStreamSituation == 1) {
				CurrentOutStream = OutStreamsVec[OUTSTREAMF1];
				++CurrentOutStreamSituation;
			}
			else {
				CurrentOutStream = OutStreamsVec[OUTSTREAMF1];
				CurrentOutStreamSituation = 0;
			}

			FirstInputVec.clear();
			SecondInputVec.clear();
			Counter = 0;
		}

		//change input and output streams
		if (CurrentStreamSituation == 0) {
			CurrentFirstInStream = InStreamsVec[INSTREAMG0];
			CurrentSecondInStream = InStreamsVec[INSTREAMG1];
			CurrentOutStream = OutStreamsVec[OUTSTREAMF0];
			++CurrentStreamSituation;
		}
		else {
			CurrentFirstInStream = InStreamsVec[INSTREAMF0];
			CurrentSecondInStream = InStreamsVec[INSTREAMF1];
			CurrentOutStream = OutStreamsVec[OUTSTREAMG0];
			CurrentStreamSituation = 0;
		}

		RunLength *= 2;
	}

}

void ExternalMergeSort::Merge(ContainerType& FirstContainer, ContainerType& SecondContainer, ContainerType& MergedContainer) {

	int LeftIndex = 0;
	int RightIndex = 0;

	for (int i = 0; i < MergedContainer.size(); ++i) {

		//check if one index is at end --> other vec can be copied into merged container
		//compare values
		if (LeftIndex > FirstContainer.size() - 1) {
			MergedContainer[i] = SecondContainer[RightIndex++];
		}
		else if (RightIndex > SecondContainer.size() - 1) {
			MergedContainer[i] = FirstContainer[LeftIndex++];
		}
		else if (FirstContainer[LeftIndex] <= SecondContainer[RightIndex]) {
			MergedContainer[i] = FirstContainer[LeftIndex++];
		}
		else {
			MergedContainer[i] = SecondContainer[RightIndex++];
		}

	}

}