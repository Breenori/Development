#include "test_rational_t.h"
#include "number_t.h"
#include <fstream>



void test_number_t_int() {
	std::cout << "Teilaufgabe 4: alle Operationen von number_t<int> testen:\n";

	number_t<int> n(4);
	std::cout << "Test Addition: \n";
	std::cout << "erwartet: " << n << "+" << n << "=8\n";
	std::cout << "tatsächlich: " << n << "+" << n << "=" << n + n << "\n";
	std::cout << "Test " << (n + n == 8 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Subtraktion: \n";
	std::cout << "erwartet: " << n << "-" << n << "=0\n";
	std::cout << "tatsächlich: " << n << "-" << n << "=" << n - n << "\n";
	std::cout << "Test " << (n - n == 0 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Multiplikation: \n";
	std::cout << "erwartet: " << n << "*" << n << "=16\n";
	std::cout << "tatsächlich: " << n << "*" << n << "=" << n * n << "\n";
	std::cout << "Test " << (n * n == 16 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Division: \n";
	std::cout << "erwartet: " << n << "/" << n << "=1\n";
	std::cout << "tatsächlich: " << n << "/" << n << "=" << n / n << "\n";
	std::cout << "Test " << (n / n == 1 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Modulo: \n";
	std::cout << "erwartet: " << n << "%" << n << "=0\n";
	std::cout << "tatsächlich: " << n << "%" << n << "=" << n % n << "\n";
	std::cout << "Test " << (n % n == 0 ? "" : "nicht ") << "erfolgreich\n\n";

	number_t<int> m(5);

	std::cout << "Test Vergleichsoperatoren: \n";
	std::cout << "erwartet: " << n << "<" << m << " wahr\n";
	std::cout << "tatsächlich: " << n << "<" << m << "=" << (n < m ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (n < m ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << m << "<" << n << " falsch\n";
	std::cout << "tatsächlich: " << m << "<" << n << (m < n ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(m < n) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << m << ">" << n << " wahr\n";
	std::cout << "tatsächlich: " << m << ">" << n << (m > n ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (m > n ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << n << ">" << m << " falsch\n";
	std::cout << "tatsächlich: " << n << ">" << m << (n > m ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(n > m) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << n << "==" << n << " wahr\n";
	std::cout << "tatsächlich: " << n << "==" << n << (n == n ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (n == n ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << n << "==" << m << " falsch\n";
	std::cout << "tatsächlich: " << n << "==" << m << (n == m ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(n == m) ? "" : "nicht ") << "erfolgreich\n\n";
}

void test_number_t_double() {
	std::cout << "Teilaufgabe 4: alle Operationen von number_t<double> testen:\n";

	number_t<double> n(4.7);
	std::cout << "Test Addition: \n";
	std::cout << "erwartet: " << n << "+" << n << "=9.4\n";
	std::cout << "tatsächlich: " << n << "+" << n << "=" << n + n << "\n";
	std::cout << "Test " << (n + n == 9.4 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Subtraktion: \n";
	std::cout << "erwartet: " << n << "-" << n << "=0\n";
	std::cout << "tatsächlich: " << n << "-" << n << "=" << n - n << "\n";
	std::cout << "Test " << (n - n == 0 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Multiplikation: \n";
	std::cout << "erwartet: " << n << "*" << n << "=22.09\n";
	std::cout << "tatsächlich: " << n << "*" << n << "=" << n * n << "\n";
	std::cout << "Test " << (n * n == 4.7 * 4.7 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Division: \n";
	std::cout << "erwartet: " << n << "/" << n << "=1\n";
	std::cout << "tatsächlich: " << n << "/" << n << "=" << n / n << "\n";
	std::cout << "Test " << (n / n == 1 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test Modulo: \n";
	std::cout << "erwartet: " << n << "%" << n << "=0\n";
	std::cout << "tatsächlich: kompiliert nicht, weil Modulo nicht sinnvoll auf Double angewendet werden kann";
	std::cout << "Test nicht erfolgreich\n\n";

	number_t<double> m(5.2);

	std::cout << "Test Vergleichsoperatoren: \n";
	std::cout << "erwartet: " << n << "<" << m << " wahr\n";
	std::cout << "tatsächlich: " << n << "<" << m << "=" << (n < m ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (n < m ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << m << "<" << n << " falsch\n";
	std::cout << "tatsächlich: " << m << "<" << n << (m < n ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(m < n) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << m << ">" << n << " wahr\n";
	std::cout << "tatsächlich: " << m << ">" << n << (m > n ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (m > n ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << n << ">" << m << " falsch\n";
	std::cout << "tatsächlich: " << n << ">" << m << (n > m ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(n > m) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << n << "==" << n << " wahr\n";
	std::cout << "tatsächlich: " << n << "==" << n << (n == n ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (n == n ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << n << "==" << m << " falsch\n";
	std::cout << "tatsächlich: " << n << "==" << m << (n == m ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(n == m) ? "" : "nicht ") << "erfolgreich\n\n";
}

void test_operations_number_t() {
	number_t<int> n(5);
	number_t<int> m(-8);
	number_t<int> o(0);

	std::cout << "Teilaufgabe 5: alle Methoden in operations.h mit number_t<int> testen:\n";

	std::cout << "Test abs() mit positivem Wert: \n";
	std::cout << "erwartet: abs(" << n << ")=5\n";
	std::cout << "tatsächlich: abs(" << n << ")=" << ops::abs(n) << "\n";
	std::cout << "Test " << (ops::abs(n) == 5 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test abs() mit negativem Wert: \n";
	std::cout << "erwartet: abs(" << m << ")=8\n";
	std::cout << "tatsächlich: abs(" << m << "=" << ops::abs(m) << "\n";
	std::cout << "Test " << (ops::abs(m) == 5 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test divides(): \n";
	std::cout << "erwartet: divides(" << n << "," << n << ") = wahr\n";
	std::cout << "tatsächlich: divides(" << n << "," << n << ") = " << (ops::divides(n, n) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (ops::divides(n, n) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test divides(): \n";
	std::cout << "erwartet: divides(" << n << "," << m << ") = falsch\n";
	std::cout << "tatsächlich: divides(" << n << "," << m << ") = " << (ops::divides(n, m) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(ops::divides(n, m)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test equals(): \n";
	std::cout << "erwartet: equals(" << n << "," << n << ") = wahr\n";
	std::cout << "tatsächlich: equals(" << n << "," << n << ") = " << (ops::equals(n, n) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (ops::equals(n, n) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test equals(): \n";
	std::cout << "erwartet: equals(" << n << "," << m << ") = falsch\n";
	std::cout << "tatsächlich: equals(" << n << "," << m << ") = " << (ops::equals(n, m) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(ops::equals(n, m)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test gcd(): \n";
	std::cout << "erwartet: gcd(" << n << "," << n << ") =5\n";
	std::cout << "tatsächlich: gcd(" << n << "," << n << ") = " << ops::gcd(n, n) << "\n";
	std::cout << "Test " << (ops::gcd(n, n) == 5 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test gcd(): \n";
	std::cout << "erwartet: gcd(" << n << "," << m << ") =1\n";
	std::cout << "tatsächlich: gcd(" << n << "," << m << ") = " << ops::gcd(n, m) << "\n";
	std::cout << "Test " << (ops::gcd(n, m) == 1 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test is_negative() mit positivem Wert: \n";
	std::cout << "erwartet: is_negative(" << n << ") falsch\n";
	std::cout << "tatsächlich: is_negative(" << n << ")=" << (ops::is_negative(n) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(ops::is_negative(n)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test equals(): mit negativem Wert\n";
	std::cout << "erwartet: is_negative(" << m << ") wahr\n";
	std::cout << "tatsächlich: is_negative(" << m << ")=" << (ops::is_negative(m) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (ops::is_negative(m) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test is_zero() mit Nicht 0: \n";
	std::cout << "erwartet: is_zero(" << n << ") falsch\n";
	std::cout << "tatsächlich: is_zero(" << n << ")=" << (ops::is_zero(n) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (!(ops::is_zero(n)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test is_zero() mit 0:\n";
	std::cout << "erwartet: is_zero(" << o << ") wahr\n";
	std::cout << "tatsächlich: is_zero(" << o << ")=" << (ops::is_zero(o) ? " wahr" : " falsch") << "\n";
	std::cout << "Test " << (ops::is_zero(o) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test negate() mit positivem Wert: \n";
	std::cout << "erwartet: negate(" << n << ") =-5\n";
	std::cout << "tatsächlich: negate(" << n << ")=" << ops::negate(n) << "\n";
	std::cout << "Test " << (ops::negate(n) == -5 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test negatve() mit negativem Wert: \n";
	std::cout << "erwartet: negate(" << m << ")=-8\n";
	std::cout << "tatsächlich: negate(" << m << ")=" << ops::negate(n) << "\n";
	std::cout << "Test " << (ops::negate(m) == -8 ? "" : "nicht ") << "erfolgreich\n\n";
}

void test_nelms_number_int() {
	std::cout << "Teilaufgabe 6: alle Methoden im namespace nelms mit number_t<int> testen:\n";

	std::cout << "Test zero<number_t<int>>(): \n";
	std::cout << "erwartet: zero<number<int>>()=0\n";
	std::cout << "tatsächlich: zero<number_t<int>>()=" << nelms::zero<number_t<int>>() << "\n";
	std::cout << "Test " << (nelms::zero<number_t<int>>() == 0 ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "Test one<number_t<int>>(): \n";
	std::cout << "erwartet: one<number<int>>()=1\n";
	std::cout << "tatsächlich: one<number_t<int>>()=" << nelms::one<number_t<int>>() << "\n";
	std::cout << "Test " << (nelms::one<number_t<int>>() == 1 ? "" : "nicht ") << "erfolgreich\n\n";
}


void test_normalize()
{
	std::cout << "Teilaufgabe 5 aus Übungszettel 3: Normalize\n";

	// normalize to whole number, negative numbers
	rational_t r(number_t<int>(-10), number_t<int>(-5));
	r.normalize();
	std::cout << "normalize (-10/-5)\n";
	std::cout << "erwartet: 2\n";
	std::cout << "tatsächlich: " << r << "\n";
	std::cout << "Test " << (r == number_t<int>(2) ? "" : "nicht ") << "erfolgreich\n\n";

	// already normalized, one negative number
	rational_t t(number_t<int>(-3), number_t<int>(5));
	t.normalize();
	std::cout << "normalize (-3/5):\n";
	std::cout << "erwartet: (-3/5)\n";
	std::cout << "tatsächlich: " << t << "\n";
	std::cout << "Test " << (t == rational_t(number_t<int>(-3), number_t<int>(5)) ? "" : "nicht ") << "erfolgreich\n\n";
}

void test_constructors()
{
	std::cout << "Teilaufgabe 12 aus Übungszettel 3 Konstruktoren:\n";


	// default constructor
	std::cout << "default constructor:\n";
	std::cout << "erwartet: 0\n";
	std::cout << "tatsächlich " << rational_t<number_t<int>>() << "\n";
	std::cout << "Test " << (rational_t<number_t<int>>() == number_t<int>(0) ? "" : "nicht ") << "erfolgreich\n\n";

	// one parameter
	std::cout << "one parameter constructor:\n";
	std::cout << "erwartet: -8\n";
	std::cout << "tatsächlich " << rational_t(number_t<int>(-8)) << "\n";
	std::cout << "Test " << (rational_t<number_t<int>>(-8) == number_t<int>(-8) ? "" : "nicht ") << "erfolgreich\n\n";


	// two parameter
	rational_t r(number_t<int>(2), number_t<int>(10));
	std::cout << "two parameter constructor:\n";
	std::cout << "erwartet: (1/5)\n";
	std::cout << "tatsächlich " << r << "\n";
	std::cout << "Test " << (r == rational_t(number_t<int>(1), number_t<int>(5)) ? "" : "nicht ") << "erfolgreich\n\n";


	// two parameter, denominator 0
	std::cout << "denominator = 0:\n";
	std::cout << "erwartet: DivideByZeroError\n";
	std::cout << "tatsächlich:\n";

	try {
		rational_t s(number_t<int>(10), number_t<int>(0));
		std::cout << s << "\n";
		std::cout << "Test nicht erfolgreich\n\n";
	}
	catch (DivideByZeroError e) {
		std::cout << e.what() << "\n";
		std::cout << "Test erfolgreich\n\n";
	}

	// copy constructor
	std::cout << "copy constructor:\n";
	std::cout << "erwartet: (1/5)\n";
	std::cout << "tatsächlich " << rational_t(r) << "\n";
	std::cout << "Test " << (rational_t(r) == r ? "" : "nicht ") << "erfolgreich\n\n";

}

void test_scan()
{
	std::cout << "Teilaufgabe 7 aus Übungszettel 3: Scan\n";
	// test regular cin
	rational_t<number_t<int>> r{};

	std::cout << "regular cin: ";
	std::cin >> r;
	std::cout << r << "\n";

	// test regular file stream
	std::cout << "filestream: ";
	std::ifstream ifs("test_scan.txt");
	ifs >> r;
	std::cout << "erwartet: 5/8\n";
	std::cout << "tatsächlich: " << r << "\n";
	std::cout << "Test " << (r == rational_t(number_t<int>(5), number_t<int>(8)) ? "" : "nicht ") << "erfolgreich\n\n";


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
		std::cout << "Test erfolgreich\n\n";
	}


}

void test_get_numerator()
{
	std::cout << "Teilaufgabe 10 aus Übungszettel 3: get_numerator\n";
	rational_t<number_t<int>> r{};
	std::cout << "erwartet: 0\n";
	std::cout << "tatsächlich: " << r.get_numerator() << "\n";
	std::cout << "Test " << (r.get_numerator() == 0 ? "" : "nicht ") << "erfolgreich\n\n";

}

void test_get_denominator()
{
	std::cout << "Teilaufgabe 10 aus Übungszettel 3: get_denominator\n";

	rational_t r{ 9 };
	std::cout << "erwartet: 1\n";
	std::cout << "tatsächlich: " << r.get_denominator() << "\n";
	std::cout << "Test " << (r.get_denominator() == 1 ? "" : "nicht ") << "erfolgreich\n\n";
}

void test_is_negative()
{
	std::cout << "Teilaufgabe 11 aus Übungszettel 3: is_negative\n";

	// positive
	rational_t<number_t<int>> r{ 9 };
	std::cout << "rational_t<number_t<int>> r{ 9 }\n";
	std::cout << "erwartet: false\n";
	std::cout << "tatsächlich: " << (r.is_negative()? "true": "false") << "\n";
	std::cout << "Test " << (!r.is_negative() ? "" : "nicht ") << "erfolgreich\n\n";


	// negative
	r = number_t<int>(-10);
	std::cout << "r = number_t<int>(-10)\n";
	std::cout << "erwartet: true\n";
	std::cout << "tatsächlich: " << (r.is_negative() ? "true" : "false") << "\n";
	std::cout << "Test " << (r.is_negative() ? "" : "nicht ") << "erfolgreich\n\n";


	// zero
	r = number_t<int>(0);
	std::cout << "r = number_t<int>(0)\n";
	std::cout << "erwartet: false\n";
	std::cout << "tatsächlich: " << (r.is_negative() ? "true" : "false") << "\n";
	std::cout << "Test " << (!r.is_negative() ? "" : "nicht ") << "erfolgreich\n\n";

}

void test_is_positive()
{
	std::cout << "Teilaufgabe 11 aus Übungszettel 3: is_positive\n";

	// positive
	rational_t<number_t<int>> r{ 9 };
	std::cout << "rational_t<number_t<int>> r{ 9 }\n";
	std::cout << "erwartet: true\n";
	std::cout << "tatsächlich: " << (r.is_positive() ? "true" : "false") << "\n";
	std::cout << "Test " << (r.is_positive() ? "" : "nicht ") << "erfolgreich\n\n";


	// negative
	r = number_t<int>(-10);
	std::cout << "r = number_t<int>(-10)\n";
	std::cout << "erwartet: false\n";
	std::cout << "tatsächlich: " << (r.is_positive() ? "true" : "false") << "\n";
	std::cout << "Test " << (!r.is_positive() ? "" : "nicht ") << "erfolgreich\n\n";


	// zero
	r = number_t<int>(0);
	std::cout << "r = number_t<int>(0)\n";
	std::cout << "erwartet: true\n";
	std::cout << "tatsächlich: " << (r.is_positive() ? "true" : "false") << "\n";
	std::cout << "Test " << (r.is_positive() ? "" : "nicht ") << "erfolgreich\n\n";
}

void test_is_zero() {

	std::cout << "Teilaufgabe 11 aus Übungszettel 3: is_zero\n";


	// positive
	rational_t<number_t<int>> r{ 6 };
	std::cout << "rational_t<number_t<int>> r{ 9 }\n";
	std::cout << "erwartet: false\n";
	std::cout << "tatsächlich: " << (r.is_zero() ? "true" : "false") << "\n";
	std::cout << "Test " << (!r.is_zero() ? "" : "nicht ") << "erfolgreich\n\n";


	// negative
	r = number_t<int>(-6);
	std::cout << "r = number_t<int>(-10)\n";
	std::cout << "erwartet: false\n";
	std::cout << "tatsächlich: " << (r.is_zero() ? "true" : "false") << "\n";
	std::cout << "Test " << (!r.is_zero() ? "" : "nicht ") << "erfolgreich\n\n";


	// zero
	r = number_t<int>(0);
	std::cout << "r = number_t<int>(0)\n";
	std::cout << "erwartet: true\n";
	std::cout << "tatsächlich: " << (r.is_zero() ? "true" : "false") << "\n";
	std::cout << "Test " << (r.is_zero() ? "" : "nicht ") << "erfolgreich\n\n";

}

void test_assign()
{
	std::cout << "Teilaufgabe 13 von Übungszettel 3: assign\n";

	rational_t r(number_t<int>(-7), number_t<int>(4));

	// int
	std::cout << "number_t<int>: \n";
	r = number_t<int>(-5);
	std::cout << "erwartet: -5\n";
	std::cout << "tatsächlich: " << r << "\n";
	std::cout << "Test " << (r == number_t<int>(-5) ? "" : "nicht ") << "erfolgreich\n\n";

	// rational
	std::cout << "rational<number_t<int>> \n";
	r = rational_t(number_t<int>(8), number_t<int>(-4));
	std::cout << "erwartet: -2\n";
	std::cout << "tatsächlich: " << r << "\n";
	std::cout << "Test " << (r == rational_t<number_t<int>>(8,-4) ? "" : "nicht ") << "erfolgreich\n\n";


	// division by 0
	try
	{
		std::cout << "division by 0: \n";
		std::cout << "erwartet: Divide by Zero Error\n";
		r = rational_t(number_t<int>(5), number_t<int>(0));
		std::cout << "Test nicht erfolgreich\n\n";
	}
	catch (DivideByZeroError e)
	{
		std::cout << e.what();
		std::cout << "Test erfolgreich\n\n";
	}

	// self assignment
	std::cout << "self assignment: \n";
	r = r;
	std::cout << "erwartet: -2\n";
	std::cout << "tatsächlich: " << r << "\n";
	std::cout << "Test " << (r == rational_t<number_t<int>>(8, -4) ? "" : "nicht ") << "erfolgreich\n\n";
}

void test_compare()
{
	std::cout << "Teilaufgabe 14 von Übungszettel 3: Vergleichsoperatoren\n";

	rational_t higher(number_t<int>(-9), number_t<int>(-2));
	rational_t higher_(number_t<int>(-9), number_t<int>(-2));
	rational_t lower(number_t<int>(-7), number_t<int>(9));

	if (higher == higher_) std::cout << higher << " and " << higher_ << " are the same\n";
	if (higher != lower) std::cout << higher << " and " << lower << " are not the same\n";
	if (lower < higher) std::cout << lower << " is < than " << higher <<"\n";
	if (higher <= higher_) std::cout << higher << " is <= than " << higher_ << "\n";
	if (higher > lower) std::cout << higher << " is > than " << lower << "\n";
	if (higher >= higher_) std::cout << higher << " is >= than " << higher_ << "\n";


	if (!(higher == lower)) std::cout << higher << " and " << lower << " are not the same" << "\n";
	if (!(higher != higher_)) std::cout << higher << " and " << higher << " are the same" << "\n";
	if (!(higher < lower)) std::cout << higher << " is not < than " << lower << "\n";
	if (!(higher <= lower)) std::cout << higher << " is not <= than " << lower << "\n";
	if (!(lower > higher)) std::cout << lower << " is not > than " << higher << "\n";
	if (!(lower >= higher)) std::cout << lower << " is not >= than " << higher << "\n";
}

void test_compound_assignment()
{
	std::cout << "Teilaufgabe 15 von Übungszettel 3: Compound Assignment\n";


	rational_t a(number_t(8), number_t(10));
	rational_t b(number_t(10), number_t(-2));

	// add and assign
	std::cout << a << " + " << b << "\n";
	a += b;
	std::cout << "erwartet: a=-21/5\n";
	std::cout << "tatsächlich: a= " << a << "\n";  // -21/5
	std::cout << "erwartet: b=-5\n";
	std::cout << "b= " << b << "\n";
	std::cout << "Test " << (a == rational_t<number_t<int>>(number_t(-21), number_t(5)) && b==number_t(-5) ? "" : "nicht ") << "erfolgreich\n\n";

	a = rational_t(number_t(8), number_t(10));

	// sub and assign
	std::cout << a << " - " << b << "\n";
	a -= b;
	std::cout << "erwartet: a=29/5\n";
	std::cout << "a= " << a << "\n";  // 29/5
	std::cout << "erwartet: b=-5\n";
	std::cout << "b= " << b << "\n";
	std::cout << "Test " << (a == rational_t<number_t<int>>(number_t(29), number_t(5)) && b == number_t(-5) ? "" : "nicht ") << "erfolgreich\n\n";


	a = rational_t(number_t(8), number_t(10));

	// mul and assign
	std::cout << a << " * " << b << "\n";
	a *= b;
	std::cout << "erwartet: a=-4\n";
	std::cout << "a= " << a << "\n";  // -4
	std::cout << "erwartet: b=-5\n";
	std::cout << "b= " << b << "\n";
	std::cout << "Test " << (a == number_t(-4) && b == number_t(-5) ? "" : "nicht ") << "erfolgreich\n\n";

	a = rational_t(number_t(8), number_t(10));

	// div and assign
	std::cout << a << " / " << b << "\n";
	a /= b;
	std::cout << "erwartet: a=-4/25\n";
	std::cout << "a= " << a << "\n";  // -4/25
	std::cout << "erwartet: b=-5\n";
	std::cout << "b= " << b << "\n";
	std::cout << "Test " << (a == rational_t<number_t<int>>(number_t(-4), number_t(25)) && b == number_t(-5) ? "" : "nicht ") << "erfolgreich\n\n";

	
	// division by 0
	std::cout << a << " / " << 0 << "\n";
	std::cout << "erwartet: Divide By Zero Error\n";

	try
	{
		a /= number_t(0);
		std::cout << a << "\n\n";
	}
	catch (DivideByZeroError e)
	{
		std::cout <<"tatsächlich: " << e.what() << "\n";
	}

}

void test_calculations()
{
	std::cout << "Teilaufgabe 16 von Übungszettel 3: Rechenoperationen\n";

	rational_t a(number_t(8), number_t(10));
	rational_t b(number_t(10), number_t(-2));

	std::cout<< "erwartet: " << a << " + " << b << " = " << "-21/5"<< "\n";
	std::cout << "tatsächlich: " << a << " + " << b << " = " << a + b << "\n";
	std::cout << "Test " << (a+b == rational_t<number_t<int>>(number_t(-21), number_t(5)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << a << " - " << b << " = " << "29/5" << "\n";
	std::cout << "tatsächlich: " << a << " - " << b << " = " << a - b << "\n";
	std::cout << "Test " << (a-b == rational_t<number_t<int>>(number_t(29), number_t(5)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << a << " * " << b << " = " << "-4" << "\n";
	std::cout << "tatsächlich: " << a << " * " << b << " = " << a * b << "\n";
	std::cout << "Test " << (a*b == number_t(-4) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << a << " * " << b << " = " << "-4/25" << "\n";
	std::cout << "tatsächlich: " << a << " / " << b << " = " << a / b << "\n";
	std::cout << "Test " << (a/b == rational_t<number_t<int>>(number_t(-4), number_t(25)) ? "" : "nicht ") << "erfolgreich\n\n";

	// with number_t
	std::cout << "\ntest with number_t<int>:\n";

	std::cout << "erwartet: " << a << " + " << 10 << " = " << "54/5" << "\n";
	std::cout << "tatsächlich: " << a << " + " << 10 << " = " << a + number_t(10) << "\n";
	std::cout << "Test " << (a + number_t(10) == rational_t<number_t<int>>(number_t(54), number_t(5)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << a << " - " << 10 << " = " << "-46/5" << "\n";
	std::cout << "tatsächlich: " << a << " - " << 10 << " = " << a - number_t(10) << "\n";
	std::cout << "Test " << (a - number_t(10) == rational_t<number_t<int>>(number_t(-46), number_t(5)) ? "" : "nicht ") << "erfolgreich\n\n";
	
	std::cout << "erwartet: " << a << " * " << 10 << " = " << "8" << "\n";
	std::cout << "tatsächlich: " << a << " * " << 10 << " = " << a * number_t(10) << "\n";
	std::cout << "Test " << (a * number_t(10) == number_t(8) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << a << " / " << 10 << " = " << "2/25" << "\n";
	std::cout << "tatsächlich: " << a << " / " << 10 << " = " << a / number_t(10) << "\n";
	std::cout << "Test " << (a / number_t(10) == rational_t<number_t<int>>(number_t(2), number_t(25)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << a << " / " << 10 << " = " << "Divide by Zero Error" << "\n";
	try
	{
		std::cout <<"tatsächlich: " << a << " / " << 0 << " = " << a / number_t(0) << "\n";
		std::cout << "Test nicht erfolgreich\n\n";
	}
	catch (DivideByZeroError e)
	{
		std::cout <<"tatsächlich: " <<  e.what();
		std::cout << "Test erfolgreich\n\n";
	}

	// with number_t first

	std::cout << "\ntest with number_t<int> first:\n";

	std::cout << "erwartet: " << 10 << " + " << a << " = " << "54/5" << "\n";
	std::cout << "tatsächlich: " << 10 << " + " << a << " = " << number_t(10)+a << "\n";
	std::cout << "Test " << (number_t(10)+a == rational_t<number_t<int>>(number_t(54), number_t(5)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << 10 << " - " << a << " = " << "46/5" << "\n";
	std::cout << "tatsächlich: " << 10 << " - " << a << " = " << number_t(10) - a << "\n"; // 46/5
	std::cout << "Test " << (number_t(10) - a == rational_t<number_t<int>>(number_t(46), number_t(5)) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << 10 << " * " << a << " = " << "8" << "\n";
	std::cout << "tatsächlich: " << 10 << " * " << a << " = " << number_t(10)*a << "\n";
	std::cout << "Test " << (number_t(10)*a == number_t(8) ? "" : "nicht ") << "erfolgreich\n\n";

	std::cout << "erwartet: " << 10 << " / " << a << " = " << "25/2" << "\n";
	std::cout << "tatsächlich: " << 10 << " / " << a << " = " << number_t(10) / a << "\n"; // 25/2
	std::cout << "Test " << (number_t(10) / a == rational_t<number_t<int>>(number_t(25), number_t(2)) ? "" : "nicht ") << "erfolgreich\n\n";

}


void test_rational_number_int() {

	number_t<int> n(4);
	number_t<int> d(6);

	rational_t<number_t<int>> r(n, d);

	std::cout << "Teilaufgabe 1: rational_t mit number_t<int> testen:\n";

	test_normalize();

	test_scan();

	test_get_numerator();
	test_get_denominator();

	test_is_negative();
	test_is_positive();
	test_is_zero();

	test_constructors();

	test_assign();

	test_compare();

	test_compound_assignment();

	test_calculations();
}