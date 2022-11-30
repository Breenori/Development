#ifndef FILE_MANIPULATOR_H
#define FILE_MANIPULATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileManipulator {
public:
	typedef std::string				FileName;
	typedef std::vector<FileName>	FileNameVec;
	typedef int						ValueType;

	static void FillRandomly(FileName const& Destination, size_t NumElements = 100, int const Minimum = 0, int const Maximum = 100);
	static int	SplitFile(FileName const& Source, FileNameVec const& DestinationVec);
	static void CopyFile(FileName const& Source, FileName const& Destination);
	static std::vector<ValueType> ReadFromFile(FileName const& Source);
	static std::ostream& WriteOut(std::vector<ValueType> Values, std::ostream& OutStream);

private:

};

#endif