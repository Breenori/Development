#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "rational_t.h"

class rational_test
{
public:
	static bool test_invalid_rational();
	static bool test_invalid_division();

	static bool test_negative_normalize_and_add_of_zero();
	static bool test_normalized_and_mul_of_zero();
	static bool test_non_normalized_and_sub_of_zero();
	
	static void test_whole_nr_print();
	static void test_rat_nr_print();

	static bool test_whole_nr_scan();
	static bool test_rat_nr_scan();
	static bool test_inv_nr_scan();

	static bool test_default_init();
	static bool test_int_init();
	static bool test_rat_init();
	static bool test_copy_init();

	static bool test_ge_pos();
	static bool test_ge_neg();

	static bool test_ne_pos();
	static bool test_ne_neg();

	static bool test_eq_pos();
	static bool test_eq_neg();

	static bool test_s_pos();
	static bool test_s_neg();

	static bool test_g_pos();
	static bool test_g_neg();

	static bool test_se_pos();
	static bool test_se_neg();

	
	static bool test_comp_ass_add();
	static bool test_comp_ass_sub();
	static bool test_comp_ass_mul();
	static bool test_comp_ass_div();

	static bool test_add();
	static bool test_sub();
	static bool test_mul();
	static bool test_div();


private:

	static bool test_normalize(rational_t & input,rational_t const& result);

	static void test_print(rational_t const& r);

	static void test_scan(rational_t & r,std::string const & filename);

	static bool test_ge(rational_t const& rhs, rational_t const& lhs);
	static bool test_eq(rational_t const& rhs, rational_t const& lhs);
	static bool test_ne(rational_t const& rhs, rational_t const& lhs);
	static bool test_se(rational_t const& rhs, rational_t const& lhs);
	static bool test_s(rational_t const& rhs, rational_t const& lhs);
	static bool test_g(rational_t const& rhs, rational_t const& lhs);

};

