#ifndef AP_TEST
# define AP_TEST

/*
* ----- Includes. -----
*/
#include "arithmetic_parser.h"

/*
* ----- Prototypes. -----
*/
void helper_tester(auto const& xpr, std::string const& exp_output);
bool test_division_zero();
bool test_empty();
bool test_single_numbers();
bool test_simple_operations();
bool test_nonsense();
bool test_custom();

#endif