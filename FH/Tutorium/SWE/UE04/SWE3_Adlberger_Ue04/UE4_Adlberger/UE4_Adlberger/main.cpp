#include "rational_t.h"
#include "test.h"

int main() {

	std::cout << "Test template default value:\n";
	 test_addition();
	 test_sub();
	 test_multiplication();
	 test_division();

	 std::cout << "Test number_t in rational_t:\n";
	  test_number_t();

	  std::cout << "Test number_t clas in rational_t:\n";
	  test_number_class();

	  std::cout << "Test inverse: \n";
	  test_inverse();


	  std::cout << " Test Operatoren: \n ";
	   test_operators();
	  std::cout << "Testing Read file:";
	  std::cout << "\nNot valid:";
	  test_read_file_not_valid_file();
	  std::cout << "\nValid:";
	  test_read_file_valid();
	  std::cout << "Wrong rational number in file:\n";
	  std::cout << "letter in file\n\n";
	  //letter in file
	  void test_read_file_false1();
	  std::cout << "\n\nNo '/' in file\n\n";
	  // not / in file
	  void test_read_file_false2();

	 
	return 0;
}