#include "test_rational_t.h"
#include <typeinfo>
#include "Div_by_Zero.h"
#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#if defined(_MSVC_LANG)  // MS compiler
#   if _MSVC_LANG < 201703
#       error Please compile for C++17 or higher
#   endif
#else  // other compiler
#   if __cplusplus < 201703
#       error Please compile for C++17 or higher
#   endif
#endif
//overall
bool test_routine() {
	std::cout << "\nC++.Version.Check:\n";
	std::cout << "\n" << __cplusplus << "\n";
	std::cout << "\n" << _MSVC_LANG << "\n";
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	test_constructor();
	std::cout << std::endl;
	test_block_helper();
	std::cout << std::endl;
	test_block_operators();
	std::cout << std::endl;
	test_block_overloading();
	std::cout << std::endl;
	test_block_cmpnd_assgn_op();
	std::cout << std::endl;
	test_block_cmpr_op();
	std::cout << std::endl;
	test_block_etc();
	std::cout << std::endl;
	test_block_lhs_rhs_op();
	std::cout << std::endl;
	return EXIT_SUCCESS;
}
#pragma region Integrated_Tests
void test_constructor() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST00:\n";
	test_cpy();
	std::cout << "\nTEST01:\n";
	test_constr_one_arg();
	std::cout << "\nTEST02:\n";
	test_constr_two_arg();
}
void test_block_helper() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST03:\n";
	test_get_num();
	std::cout << "\nTEST04:\n";
	test_get_denom();
	std::cout << "\nTEST05:\n";
	test_set_num();
	std::cout << "\nTEST06:\n";
	test_set_denom();
	std::cout << "\nTEST07:\n";
	test_asstr();
	std::cout << "\nTEST08:\n";
	test_is_neg();
	std::cout << "\nTEST09:\n";
	test_is_pos();
	std::cout << "\nTEST10:\n";
	test_is_zer();
}
void test_block_operators() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST11:\n";
	test_add();
	std::cout << "\nTEST12:\n";
	test_sub();
	std::cout << "\nTEST13:\n";
	test_mul();
	std::cout << "\nTEST14:\n";
	test_div();
}
void test_block_overloading() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST15:\n";
	test_add_op();
	std::cout << "\nTEST16:\n";
	test_sub_op();
	std::cout << "\nTEST17:\n";
	test_mul_op();
	std::cout << "\nTEST18:\n";
	test_div_op();
}
void test_block_cmpnd_assgn_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST19:\n";
	test_add_op_ass();
	std::cout << "\nTEST20:\n";
	test_sub_op_ass();
	std::cout << "\nTEST21:\n";
	test_mul_op_ass();
	std::cout << "\nTEST22:\n";
	test_div_op_ass();
}
void test_block_cmpr_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST23:\n";
	test_same_op();
	std::cout << "\nTEST24:\n";
	test_not_same_op();
	std::cout << "\nTEST25:\n";
	test_smaller_op();
	std::cout << "\nTEST26:\n";
	test_smaller_same_op();
	std::cout << "\nTEST27:\n";
	test_bigger_op();
	std::cout << "\nTEST28:\n";
	test_bigger_same_op();
}
void test_block_etc() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST29:\n";
	test_cpy_swap_idiom();
	std::cout << "\nTEST30:\n";
	test_is_consis();
	std::cout << "\nTEST31:\n";
	test_gcd();
	std::cout << "\nTEST32:\n";
	test_norm();
}
void test_block_lhs_rhs_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nTEST33:\n";
	test_lhs_rhs_add();
	std::cout << "\nTEST34:\n";
	test_lhs_rhs_sub();
	std::cout << "\nTEST35:\n";
	test_lhs_rhs_mul();
	std::cout << "\nTEST36:\n";
	test_lhs_rhs_div();
	std::cout << "\nTEST37:\n";
	test_div_by_zero_exc();
	std::cout << "\nTEST38:\n";
	//test_scan();
}
#pragma endregion
#pragma region Unit_Tests
//constructor
void test_cpy() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	rational_t out = tester;
	std::cout << "Source:\n";
	tester.print();
	std::cout << "Copied:\n";
	out.print();
}
void test_constr_one_arg() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2 };
	tester.print();
}
void test_constr_two_arg() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	tester.print();
}
//helper
void test_get_num() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	std::cout << "Get_Numerator: " << tester.get_numerator() << "\n";
}
void test_get_denom() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	std::cout << "Get_Denominator: " << tester.get_denominator() << std::endl;
}
void test_set_num() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	int setter{ 3 };
	std::cout << "Source: ";
	tester.print();
	tester.set_numerator(setter);
	std::cout << "Input: " << setter << "\n" << "Setted: ";
	tester.print();
	std::cout << "\n";
}
void test_set_denom() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	int setter{ 4 };
	std::cout << "Source: ";
	tester.print();
	tester.set_denominator(setter);
	std::cout << "Input: " << setter << "\n" << "Setted: ";
	tester.print();
	std::cout << "\n";
}
void test_asstr() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	std::string output = tester.as_string();
	std::cout << "Variable conversion typeID:\n" << typeid(output).name() << "\n";
	std::cout << output << "\n";
}
void test_is_neg() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	std::cout << "Source: ";
	tester.print();
	std::cout << "\n";
	std::cout << std::boolalpha << tester.is_negative()<<"\n";
	if (tester.is_negative())
	{
		std::cout << "Is negative.\n";
	}
	else
	{
		std::cout << "Not negative.\n";
	}
}
void test_is_pos() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	std::cout << "Source: ";
	tester.print();
	std::cout << "\n";
	std::cout << std::boolalpha << tester.is_positive()<<"\n";
	if (!tester.is_positive())
	{
		std::cout << "Is positive.\n";
	}
	else
	{
		std::cout << "Not positive.\n";
	}
}
void test_is_zer() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t tester{ 2,3 };
	std::cout << "Source: ";
	tester.print();
	std::cout << "\n";
	std::cout << std::boolalpha << tester.is_zero()<<"\n";
	if (tester.is_positive())
	{
		std::cout << "Is zero.\n";
	}
	else
	{
		std::cout << "Not zero.\n";
	}
}
//operators
void test_add() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.add(b);
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\n";
}
void test_sub() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.sub(b);
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\n";
}
void test_mul() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.mul(b);
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\n";
}
void test_div() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.div(b);
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\n";
}
//overloading
void test_add_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t c = a + b;
	c.print();
	std::cout << "\n";
}
void test_sub_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t c = a - b;
	c.print();
	std::cout << "\n";
}
void test_mul_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t c = a * b;
	c.print();
	std::cout << "\n";
}
void test_div_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t c = a / b;
	c.print();
	std::cout << "\n";
}
//compound assignment operators
void test_add_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a += b;
	a.print();
	std::cout << "\n";
}
void test_sub_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a -= b;
	a.print();
	std::cout << "\n";
}
void test_mul_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a *= b;
	a.print();
	std::cout << "\n";
}
void test_div_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a /= b;
	a.print();
	std::cout << "\n";
}
//compare operators
void test_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	if (a == b)
	{
		std::cout << "Same.\n";
	}
	else
	{
		std::cout << "Not same.\n";
	}
}
void test_not_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	if (a != b)
	{
		std::cout << "Same.\n";
	}
	else
	{
		std::cout << "Not same.\n";
	}
}
void test_smaller_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	if (a < b)
	{
		std::cout << "Smaller.\n";
	}
	else
	{
		std::cout << "Not smaller.\n";
	}
}
void test_smaller_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	if (a <= b)
	{
		std::cout << "Smaller-same.\n";
	}
	else
	{
		std::cout << "Not smaller-same.\n";
	}
}
void test_bigger_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	if (a > b)
	{
		std::cout << "Bigger.\n";
	}
	else
	{
		std::cout << "Not bigger.\n";
	}
}
void test_bigger_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	if (a >= b)
	{
		std::cout << "Bigger-same.\n";
	}
	else
	{
		std::cout << "Not bigger-same.\n";
	}
}
//cpy swap idiom
void test_cpy_swap_idiom() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a = b;
	std::cout << "Copy-swaped-idiom:\n";
	a.print();
}
void test_is_consis() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "Source: <2/0>\n";
	try
	{
		rational_t a{ 2,0 };
	}
	catch (const DivideByZeroError&)
	{
		std::cout << "Denominator is zero.Not consistent.\n";
	}
}
void test_gcd() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	std::cout << "Source1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "Static foo.\nExplanatory in normalize()!!!\n";
}
void test_norm() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 20,30 };
	rational_t b{ 12,4 };
	std::cout << "Source1: ";
	std::cout << a;
	a.print();
	std::cout << "\nSource2: ";
	std::cout << b;
	b.print();
	std::cout << "\nNormalized through print_foos.\n";
}
//lhs & rhs compatibility
void test_lhs_rhs_add() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t result;
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nSource3: ";
	std::cout << c;
	std::cout << "\nSource4: ";
	std::cout << d;
	std::cout << "\nResults:\nLHS-RHS\nRHS-LHS\nInt-Rational:\n";
	result = c + a;
	result.print();
	result = d + b;
	result.print();
}
void test_lhs_rhs_sub() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t result;
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nSource3: ";
	std::cout << c;
	std::cout << "\nSource4: ";
	std::cout << d;
	std::cout << "\nResults:\nLHS-RHS\nRHS-LHS\nInt-Rational:\n";
	result = c - a;
	result.print();
	result = d - b;
	result.print();
}
void test_lhs_rhs_mul() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t result;
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nSource3: ";
	std::cout << c;
	std::cout << "\nSource4: ";
	std::cout << d;
	std::cout << "\nResults:\nLHS-RHS\nRHS-LHS\nInt-Rational:\n";
	result = c * a;
	result.print();
	result = d * b;
	result.print();
}
void test_lhs_rhs_div() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a{ 2,3 };
	rational_t b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t result;
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nSource3: ";
	std::cout << c;
	std::cout << "\nSource4: ";
	std::cout << d;
	std::cout << "\nResults:\nLHS-RHS\nRHS-LHS\nInt-Rational:\n";
	result = c / a;
	result.print();
	result = d / b;
	result.print();
}
//exception
void test_div_by_zero_exc() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a(0,0);
	int b{ 0 };
	rational_t c;
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	std::cout << b;
	try
	{
		c = b / a;
	}
	catch (const DivideByZeroError& e)
	{
		std::cout<< e.what();
	}
}
void test_scan() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t a;
	std::cout << "\nManual input:\n";
	try
	{
	a.scan();
	std::cout << "\nResult:\n";
	a.print();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "Scan error.\n";
	}
}
#pragma endregion



