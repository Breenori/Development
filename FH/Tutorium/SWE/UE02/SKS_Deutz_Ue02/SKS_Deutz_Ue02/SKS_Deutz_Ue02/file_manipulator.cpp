#include "file_manipulator.h"
#include <random>
#include <chrono>

typedef	std::chrono::system_clock				Clock;
typedef std::default_random_engine				Random;
typedef std::uniform_real_distribution<double>	RealDist;
typedef std::uniform_int_distribution<int>		IntDist;

void FileManipulator::FillRandomly(FileName const& Destination, size_t NumElements, int const Minimum, int const Maximum){

	//set seed and define generator
	unsigned int	Seed = Clock::now().time_since_epoch().count();
	Random			Generator{ Seed };
	IntDist			DisI{ Minimum, Maximum };

	std::ofstream Out{ Destination };

	//get random numbers between minimum and maximum and print them
	while (Out && (NumElements-- > 0)) {

		ValueType Value = DisI(Generator);

		Out << Value;

		Out << " ";

	}

	Out.close();

}

int FileManipulator::SplitFile(FileName const& Source, FileNameVec const& DestinationVec) {

	std::ifstream In{ Source };
	std::vector<std::ofstream*> OutVec;

	int DestinationSize = DestinationVec.size();

	//fill OutVec with ofstream with filenames from DestinationVec
	for (int i = 0; i < DestinationSize; ++i) {

		OutVec.push_back(new std::ofstream(DestinationVec[i]));

	}

	int n = 0;
	ValueType Value;

	//write value for value alternately in every file from destinationVec
	while (In >> Value) {

		std::ofstream& OutFile{ *(OutVec[n % DestinationSize]) };

		if (OutFile)
			OutFile << Value << " ";

		++n;
	}

	//delete OutVec
	for (int i = 0; i < OutVec.size(); ++i) {

		delete OutVec[i];

	}

	return n;
}

void FileManipulator::CopyFile(FileName const& Source, FileName const& Destination) {

	std::ifstream In{ Source };
	std::ofstream Out{ Destination };

	ValueType Value;

	//read every value and write it to new file
	while (In >> Value) {

		Out << Value << " ";

	}

	In.close();
	Out.close();

}

std::vector<FileManipulator::ValueType> FileManipulator::ReadFromFile(FileName const& Source) {

	std::ifstream In{ Source };
	ValueType Value;
	std::vector<ValueType> ResultVec;

	//read values from source file and save it in resutl vec
	while (In >> Value)
		ResultVec.push_back(Value);

	In.close();

	return ResultVec;
}

std::ostream& FileManipulator::WriteOut(std::vector<ValueType> Values, std::ostream& OutStream) {

	for (int i = 0; i < Values.size(); ++i)
		OutStream << Values[i] << " ";

	return OutStream;
}