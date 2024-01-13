#ifndef file_manipulator_h
#define file_manipulator_h

#include <string>
#include <vector>

class FileManipulator {
public:
	using value_t = std::string;
	using cont_t = std::vector<value_t>;

	//fills string with n random chars
	static void fillRandomly(value_t const& dst, size_t n = 100, int const num_letters = 1);
	//splits file content into multiple parts
	static std::size_t partition(value_t const& src, cont_t const& dst);
	// copy string to file
	static void copy(std::string const& src, std::string const& dst);
	//print string to ostream
	static std::ostream& print(std::string const& src, std::ostream& out);
	//gets value from file at specific index
	static bool getValue(int s, int k, int i, std::string inName, std::string& val);
	//writes value to ofstream, appends
	static void writeTo(std::string const& Value, std::string outName);

private:

};

#endif // !file_manipulator_h
