#include "rational_test.h"

bool rational_test::test_normalize(rational_t& input, rational_t const& result)
{
	std::cout << "Test normalize\n";
	input += 0;
	return input == result;
}

void rational_test::test_print(rational_t const& r)
{
	std::cout << "Test print\n";
	r.print();
}

void rational_test::test_scan(rational_t& r, std::string const& filename)
{
	std::cout << "Test scan\n";
	std::ifstream ifs(filename);
	ifs >> r;
	std::cout << "Scaned element " << r << "\n";
	ifs.close();

}


bool rational_test::test_ge(rational_t const& rhs, rational_t const& lhs)
{
	return rhs >= lhs;
}

bool rational_test::test_eq(rational_t const& rhs, rational_t const& lhs)
{
	return rhs == lhs;
}

bool rational_test::test_ne(rational_t const& rhs, rational_t const& lhs)
{
	return rhs != lhs;
}

bool rational_test::test_se(rational_t const& rhs, rational_t const& lhs)
{
	return rhs <= lhs;
}

bool rational_test::test_s(rational_t const& rhs, rational_t const& lhs)
{
	return rhs < lhs;
}

bool rational_test::test_g(rational_t const& rhs, rational_t const& lhs)
{
	return rhs > lhs;
}

bool rational_test::test_invalid_rational()
{
	try {
		rational_t r(0, 0);
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

bool rational_test::test_invalid_division()
{
	try {
		rational_t r(1, 2);
		rational_t l(0, 3);
		r /= l;
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

bool rational_test::test_negative_normalize_and_add_of_zero()
{
	rational_t exp(1, 3);
	rational_t in(-1, -3);
	in += 0;
	return exp == in;
}

bool rational_test::test_normalized_and_mul_of_zero()
{
	rational_t exp(0, 3);
	rational_t in(1, 3);
	in *= 0;
	return exp == in;

}

bool rational_test::test_non_normalized_and_sub_of_zero()
{
	rational_t exp(1, 2);
	rational_t in(2, 4);
	in -= 0;
	return exp == in;
}

void rational_test::test_whole_nr_print()
{
	rational_t r(5);
	test_print(r);
}

void rational_test::test_rat_nr_print()
{
	rational_t r(5, 6);
	test_print(r);
}

bool rational_test::test_whole_nr_scan()
{
	rational_t r(1, 1);
	test_scan(r, "whole_nr_scan.txt");
	return r != rational_t(1, 1);
}

bool rational_test::test_rat_nr_scan()
{
	rational_t r(1, 1);
	test_scan(r, "rational_nr_scan.txt");
	return r != rational_t(1, 1);
}

bool rational_test::test_inv_nr_scan()
{
	rational_t r(1, 1);
	test_scan(r, "invalid_scan.txt");
	return r == rational_t(1, 1);
}

bool rational_test::test_default_init()
{
	rational_t r;
	r.print();
	return rational_t() == rational_t(1, 1);
}

bool rational_test::test_int_init()
{
	rational_t r(2);
	r.print();
	return r == rational_t(2);
}

bool rational_test::test_rat_init()
{
	rational_t r(2, 3);
	r.print();
	return r == rational_t(2, 3);
}

bool rational_test::test_copy_init()
{
	rational_t r(3, 4);
	rational_t r_c = r;
	return r == r_c;
}

bool rational_test::test_ge_pos()
{
	return test_ge(rational_t(1, 2), rational_t(1, 4)) &&
		test_ge(rational_t(1, 2), rational_t(1, 2));
}

bool rational_test::test_ge_neg()
{
	return !test_ge(rational_t(1, 4), rational_t(1, 2));
}

bool rational_test::test_ne_pos()
{
	return test_ne(rational_t(1, 2), rational_t(1, 4));
}

bool rational_test::test_ne_neg()
{
	return !test_ne(rational_t(1, 2), rational_t(1, 2));
}

bool rational_test::test_eq_pos()
{
	return test_eq(rational_t(1, 2), rational_t(1, 2));
}

bool rational_test::test_eq_neg()
{
	return !test_eq(rational_t(1, 4), rational_t(1, 2));
}

bool rational_test::test_s_pos()
{
	return test_s(rational_t(1, 4), rational_t(1, 2));
}

bool rational_test::test_s_neg()
{
	return !(test_s(rational_t(1, 2), rational_t(1, 4)) &&
		test_s(rational_t(1, 2), rational_t(1, 2)));
}

bool rational_test::test_g_pos()
{
	return test_g(rational_t(1, 2), rational_t(1, 4));
}

bool rational_test::test_g_neg()
{
	return !(test_g(rational_t(1, 4), rational_t(1, 2)) &&
		test_g(rational_t(1, 2), rational_t(1, 2)));
}

bool rational_test::test_se_pos()
{
	return test_se(rational_t(1, 4), rational_t(1, 2)) &&
		test_se(rational_t(1, 2), rational_t(1, 2));
}

bool rational_test::test_se_neg()
{
	return !test_se(rational_t(1, 2), rational_t(1, 4));
}


bool rational_test::test_comp_ass_add()
{
	rational_t r(1, 2);
	r += 1;
	return r == rational_t(3, 2);
}

bool rational_test::test_comp_ass_sub()
{

	rational_t r(1, 2);
	r -= 1;
	return r == rational_t(-1, 2);
}

bool rational_test::test_comp_ass_mul()
{

	rational_t r(1, 2);
	r *= 1;
	return r == rational_t(1, 2);
}

bool rational_test::test_comp_ass_div()
{

	rational_t r(1, 2);
	r /= 1;
	return r == rational_t(1, 2);
}

bool rational_test::test_add()
{
	return 1 + rational_t(1, 2) == rational_t(3, 2);
}

bool rational_test::test_sub()
{
	return 1 - rational_t(1, 2) == rational_t(1, 2);
}

bool rational_test::test_mul()
{
	return 1 * rational_t(1, 2) == rational_t(1, 2);
}

bool rational_test::test_div()
{
	return 1 / rational_t(1, 2) == rational_t(2);
}
