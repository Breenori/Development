#include "test_rational_t.h"
#include <fstream>

void test_example()
{
	rational_t r(-1, 2);

	std::cout << r * -10 << "\n" << r * rational_t(20, -2) << "\n";

	r = 7;
	std::cout << r + rational_t(2, 3) << "\n" << 10 / r / 2 + rational_t(6, 5) << "\n";
}

void test_normalize()
{
	// normalize to whole number, negative numbers
	std::cout << "normalize to whole number, negative numbers:\n";
	rational_t r(-10, -5);
	r.normalize();
	std::cout << r << "\n";

	// already normalized, one negative number
	std::cout << "already normalized, one negative number:\n";
	rational_t t(-3, 5);
	t.normalize();
	std::cout << t << "\n";
}

void test_constructors()
{
	// default constructor
	std::cout << "default constructor:\n";
	std::cout << rational_t() << "\n";

	// one parameter
	std::cout << "one parameter constructor:\n";
	std::cout << rational_t(-8) << "\n";

	// two parameter
	std::cout << "two parameter constructor:\n";
	rational_t r(2, 10);
	std::cout << r << "\n";

	// two parameter, denominator 0
	std::cout << "denominator = 0:\n";
	try {
		rational_t s(10, 0);
		std::cout << s << "\n";
	}
	catch (DivideByZeroError e) {
		std::cout << e.what() << "\n";
	}

	// copy constructor
	std::cout << "copy constructor:\n";
	std::cout << rational_t(r) << "\n";
}

void test_scan()
{
	// test regular cin
	rational_t r{};

	std::cout << "regular cin: ";
	std::cin >> r;
	std::cout << r << "\n";

	// test regular file stream
	std::cout << "filestream: ";
	std::ifstream ifs("test_scan.txt");
	ifs >> r;
	std::cout << r << "\n";

	// test no /
	std::cout << "no /: ";
	std::cin >> r;
	std::cout << r << "\n";

	// test no numbers
	try
	{
		std::cout << "letters and special characters: ";
		std::cin >> r;
		std::cout << r << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}


	// test only /
	std::cout << "only /: ";
	std::cin >> r;
	std::cout << r << "\n";


	// test nothing after /
	try
	{
		std::cout << "nothing after /: ";
		std::cin >> r;
		std::cout << r << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}


	// test nothing before /
	try
	{
		std::cout << "nothing before /: ";
		std::cin >> r;
		std::cout << r << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}

	// test denominator 0
	std::cout << "denominator 0: ";
	try
	{
		std::cin >> r;
		std::cout << r << "\n";
	}
	catch (DivideByZeroError e)
	{
		std::cout << e.what();
	}

}

void test_get_numerator()
{
	rational_t r{};
	std::cout << "get numerator: ";
	std::cout << r.get_numerator() << "\n";
}

void test_get_denominator()
{
	rational_t r{ 9 };
	std::cout << "get denumerator: ";
	std::cout << r.get_denominator() << "\n";
}

void test_is_negative()
{
	// positive
	rational_t r{ 9 };
	if (!r.is_negative()) std::cout << r << " is not negative" << "\n";

	// negative
	r = -10;
	if (r.is_negative()) std::cout << r << " is negative" << "\n";

	// zero
	r = 0;
	if (r.is_negative()) std::cout << 0 << " is negative" << "\n";
	else std::cout << 0 << " is not negative" << "\n";
}

void test_is_positive()
{
	// positive
	rational_t r{ 9 };
	if (r.is_positive()) std::cout << r << " is positive" << "\n";

	// negative
	r = -10;
	if (!r.is_positive()) std::cout << r << " is not positive" << "\n";

	// zero
	r = 0;
	if (r.is_positive()) std::cout << 0 << " is positive" << "\n";
	else std::cout << 0 << " is not positive" << "\n";
}

void test_is_zero() {
	// is zero
	rational_t r{ 0,8 };
	if (r.is_zero()) std::cout << r << " is zero" << "\n";

	// is positive
	r = 6;
	if (!r.is_zero()) std::cout << r << " is not zero" << "\n";

	// is negative
	r = -6;
	if (!r.is_zero()) std::cout << r << " is not zero" << "\n";
}

void test_assign()
{
	rational_t r(-7, 4);

	// int
	std::cout << "int: \n";
	r = -5;
	std::cout << r << "\n";

	// rational
	std::cout << "rational: \n";
	r = rational_t(8, -4);
	std::cout << r << "\n";

	// division by 0
	try
	{
		std::cout << "division by 0: \n";
		r = rational_t(5, 0);
	}
	catch (DivideByZeroError e)
	{
		std::cout << e.what() << "\n";
	}

	// self assignment
	std::cout << "self assignment: \n";
	r = r;
	std::cout << r << "\n";
}

void test_compare()
{
	rational_t higher(-9, -2);
	rational_t higher_(-9, -2);
	rational_t lower(-7, 9);

	if (higher == higher_) std::cout << higher << " and " << higher_ << " are the same";
	if (higher != lower) std::cout << higher << " and " << higher << " are not the same";
	if (lower < higher) std::cout << lower << " is < than " << higher;
	if (higher <= higher_) std::cout << higher << " is <= than " << higher_;
	if (higher > lower) std::cout << higher << " is > than " << lower;
	if (higher >= higher_) std::cout << higher << " is >= than " << higher_;


	if (!(higher == lower)) std::cout << higher << " and " << lower << " are not the same";
	if (!(higher != higher_)) std::cout << higher << " and " << higher << " are the same";
	if (!(higher < lower)) std::cout << higher << " is not < than " << lower;
	if (!(higher <= lower)) std::cout << higher << " is not <= than " << lower;
	if (!(lower > higher)) std::cout << lower << " is not > than " << higher;
	if (!(lower >= higher)) std::cout << lower << " is not >= than " << higher;
}

void test_compound_assignment()
{
	rational_t a(8, 11);
	rational_t b(10, -3);

	// add and assign
	std::cout << a <<  " + " << b << "\n";
	a += b;
	std::cout <<"a= " << a << "\n";  // -21/5
	std::cout <<"b= " << b << "\n\n";

	a = rational_t(8, 11);

	// sub and assign
	std::cout << a << " - " << b << "\n";
	a -= b;
	std::cout << "a= " << a << "\n";  // 29/5
	std::cout << "b= " << b << "\n\n";

	a = rational_t(8, 10);

	// mul and assign
	std::cout << a << " * " << b << "\n";
	a *= b;
	std::cout << "a= " << a << "\n";  // -4
	std::cout << "b= " << b << "\n\n";

	a = rational_t(8, 10);

	// div and assign
	std::cout << a << " / " << b << "\n";
	a /= b;
	std::cout << "a= " << a << "\n";  // -4/25
	std::cout << "b= " << b << "\n\n";

	a = rational_t(8, 10);
	// add and assign with integer
	std::cout << a << " + " << 10 << "\n";
	a += 10;
	std::cout << a << "\n\n";  // 54/5

	a = rational_t(8, 10);

	
	// sub and assign with integer
	std::cout << a << " - " << 10 << "\n";
	a -= 10;
	std::cout << a << "\n\n";  // -46/5

	a = rational_t(8, 10);

	// mul and assign with integer
	std::cout << a << " * " << 10 << "\n";
	a *= 10;
	std::cout << a << "\n\n";  // 8

	a = rational_t(8, 10);

	// div and assign with integer
	std::cout << a << " / " << 10 << "\n";
	a /= 10;
	std::cout << a << "\n\n";  // 2/25

	// division by 0
	try
	{
		std::cout << a << " / " << 0 << "\n";
		a /= 0;
		std::cout << a << "\n\n"; 
	}
	catch (DivideByZeroError e)
	{
		std::cout << e.what() << "\n";
	}
	
}

void test_calculations()
{
	rational_t a(8, 10);
	rational_t b(10, -2);

	std::cout << a << " + " << b << " = " << a + b << "\n";

	std::cout << a << " - " << b << " = " << a - b << "\n";

	std::cout << a << " * " << b << " = " << a * b << "\n";

	std::cout << a << " / " << b << " = " << a / b << "\n";

	// with integers
	std::cout << a << " + " << 10 << " = " << a + 10 << "\n";

	std::cout << a << " - " << 10 << " = " << a - 10 << "\n";

	std::cout << a << " * " << 10 << " = " << a * 10 << "\n";

	std::cout << a << " / " << 10 << " = " << a / 10 << "\n";

	try
	{
		std::cout << a << " / " << 0 << " = " << a / 0 << "\n";
	}
	catch (DivideByZeroError e)
	{
		std::cout << e.what() << "\n";
	}

	// with integers first
	std::cout << 10 << " + " << a << " = " << 10 + a << "\n";

	std::cout << 10 << " - " << a << " = " << 10 - a << "\n"; // 46/5

	std::cout << 10 << " * " << a << " = " << 10 * a << "\n";

	std::cout << 10 << " / " << a << " = " << 10 / a << "\n"; // 25/2
}

