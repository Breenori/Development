#ifndef file_manipulator_h
#define file_manipulator_h

#include <string>
#include <vector>


class fileManipulator {

public:

	using value_t = std::string;
	using cont_t = std::vector<value_t>;

	static void fill_randomly_str(value_t const& dst, std::size_t n = 100, int const no_letters = 1); //dst=destination, no_letters = Länge von Elementen
	static void fill_randomly_int(value_t const& dst, std::size_t n, int const max_nr = 10);


	static std::size_t partition(value_t const& src, cont_t const& dst);
	static std::size_t re_partition(value_t const& src0, value_t const& src1, value_t const& dst);


	static std::vector<int> read(value_t const& src);
	static void write(std::vector<int>v_tmp, value_t dst);

	static void copy(value_t const& src, value_t const& dst);
	static void print(value_t const& src);




private:


};


#endif // !file_manipulator_h
