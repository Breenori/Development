#include "test_rational_t.h"
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
	try
	{
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
	}
	catch (const std::exception&)
	{
		std::cout << "Exception has occured.\n";
	}
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
	test_is_neg();
	std::cout << "\nTEST06:\n";
	test_is_zer();
	std::cout << "\nTEST07:\n";
	test_inverse();
	std::cout << "\nTEST08:\n";
	test_set_num();
	std::cout << "\nTEST09:\n";
	test_set_denom();
	std::cout << "\nTEST10:\n";
	test_lcm();
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
	test_scan();
}
#pragma endregion
#pragma region Unit_Tests
//constructor
void test_cpy() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	rational_t<number_t<int>> out = tester;
	std::cout << "\nSource:\n";
	tester.print();
	std::cout << "\nCopied:\n";
	out.print();
	std::cout << "\nExpected output:2/3\n";
	std::cout << "\nActual output:\n";
	out.print();
	std::cout << "\nIf_success:\n" << EXIT_SUCCESS;
}
void test_constr_one_arg() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2 };
	std::cout << "\nExpected output:2\n";
	std::cout << "\nActual output:\n";
	tester.print();
	std::cout << "\n" << "\nif_success:\n" << EXIT_SUCCESS;
}
void test_constr_two_arg() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	std::cout << "\nExpected output:2/3\n";
	std::cout << "\nActual output:\n";
	tester.print();
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
//helper
void test_get_num() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	std::cout << "\nExpected output:\n" << "2";
	std::cout << "\nActual output:\n" << tester.get_numerator() << "\n";
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
void test_get_denom() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	std::cout << "\nExpected output:\n" << "3";
	std::cout << "\nActual output:\n" << tester.get_denominator() << "\n";
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
void test_set_num() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	tester.print();
	tester.set_numerator(3);
	std::cout << "\nExpected output:\n" << "3/3";
	std::cout << "\nActual output:\n";
	tester.print();
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
void test_set_denom() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	tester.print();
	tester.set_denominator(4);
	std::cout << "\nExpected output:\n" << "2/4";
	std::cout << "\nActual output:\n";
	tester.print();
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
void test_is_neg() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	std::cout << "\nSource: ";
	tester.print();
	std::cout << "\n";
	std::cout << std::boolalpha << ops::is_negative(tester) << "\n";
	std::cout << "\nExpected output:\n" << std::boolalpha << ops::is_negative(tester) << "\n";
	std::cout << "\nActual output:\n";
	if (ops::is_negative(tester))
	{
		std::cout << "\nIs negative.\n";
	}
	else
	{
		std::cout << "\nNot negative.\n";
	}
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
void test_is_zer() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	std::cout << "\nSource: ";
	tester.print();
	std::cout << "\n";
	std::cout << "\nExpected output:\n" << std::boolalpha << ops::is_zero(tester) << "\n";
	std::cout << "\nActual output:\n";
	if (ops::is_zero(tester))
	{
		std::cout << "\nIs zero.\n";
	}
	else
	{
		std::cout << "\nNot zero.\n";
	}
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
void test_inverse() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> tester{ 2,3 };
	std::cout << "\nSource: ";
	tester.print();
	tester.inverse();
	std::cout << "\n";
	std::cout << "\nExpected output:\n" << "3/2\n";
	std::cout << "\nActual output:\n";
	tester.print();
	std::cout << "\nIf_success:" << EXIT_SUCCESS;
}
void test_lcm() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nStatic foo.\nExplanatory in add and sub!!!\n";
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
//operators
void test_add() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.add(b);
	std::cout << "\n";
	std::cout << "\nExpected output:\n" << "17/12\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_sub() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.sub(b);
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\nExpected output:\n" << "-1/12\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "Unknown error.Sub funkt nicht ganS.Ongoing in -= etc.";
	std::cout << "\nif_success:" << EXIT_FAILURE;
	std::cout << std::endl;
}
void test_mul() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.mul(b);
	std::cout << "\nExpected output:\n" << "6/12\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
	std::cout << std::endl;
}
void test_div() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a.div(b);
	std::cout << "\nExpected output:\n" << "8/9\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
	std::cout << std::endl;
}
//overloading
void test_add_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t<number_t<int>> c = a + b;
	std::cout << "\nExpected output:\n" << "17/12\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	c.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_sub_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t<number_t<int>> c = a - b;
	std::cout << "\nExpected output:\n" << "-1/2\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	c.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_mul_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t<number_t<int>> c = a * b;
	std::cout << "\nExpected output:6/12\n" << "\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	c.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_div_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	rational_t<number_t<int>> c = a / b;
	std::cout << "\nExpected output:\n" << "8/9\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	c.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
//compound assignment operators
void test_add_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a += b;
	std::cout << "\nExpected output:\n" << "17/12\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_sub_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a -= b;
	std::cout << "\nExpected output:\n" << "-1/2\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_mul_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a *= b;
	std::cout << "\nExpected output:\n" << "6/12\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_div_op_ass() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a /= b;
	std::cout << "\nExpected output:\n" << "8/9\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
//compare operators
void test_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nExpected output:\n" << "Same.\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	if (a == b)
	{
		std::cout << "\nSame.\n";
	}
	else
	{
		std::cout << "\nNot same.\n";
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_not_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nExpected output:\n" << "Not same.\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	if (a != b)
	{
		std::cout << "\nSame.\n";
	}
	else
	{
		std::cout << "\nNot same.\n";
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_smaller_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nExpected output:\n" << "Not smaller\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult '<': ";
	if (a < b)
	{
		std::cout << "\nSmaller.\n";
	}
	else
	{
		std::cout << "\nNot smaller.\n";
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_smaller_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nExpected output:\n" << "Smaller-same.\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	if (a <= b)
	{
		std::cout << "\nSmaller-same.\n";
	}
	else
	{
		std::cout << "\nNot smaller-same.\n";
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_bigger_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nExpected output:\n" << "Not Bigger.\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	if (a > b)
	{
		std::cout << "\nBigger.\n";
	}
	else
	{
		std::cout << "\nNot bigger.\n";
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_bigger_same_op() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nExpected output:\n" << "Bigger-same.\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	if (a >= b)
	{
		std::cout << "\nBigger-same.\n";
	}
	else
	{
		std::cout << "\nNot bigger-same.\n";
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
//cpy swap idiom
void test_cpy_swap_idiom() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	a = b;
	std::cout << "\nExpected output:\n" << "2/3\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	std::cout << "\nCopy-swaped-idiom:\n";
	a.print();
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_is_consis() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "\nSource: <2/0>\n";
	std::cout << "\nExpected output:\n" << "Exception:\n";
	std::cout << "\nActual output:\n";
	std::cout << "\nResult: ";
	try
	{
		rational_t<number_t<int>> a{ 2,0 };
	}
	catch (const DivideByZeroError&)
	{
		std::cout << "\nDenominator is zero.Not consistent.\n";
	}
}
void test_gcd() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	b.print();
	std::cout << "\nStatic foo.\nExplanatory in normalize()!!!\n";
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_norm() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 20,30 };
	rational_t<number_t<int>> b{ 12,4 };
	std::cout << "\nSource1:20/30";
	a.print();
	std::cout << "\nSource2: 12/4";
	b.print();
	std::cout << "\nNormalized through print_foos.\n";
	std::cout << "\nExpected output:\n" << "S1:2/3; S2:3\n";
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
//lhs & rhs compatibility
void test_lhs_rhs_add() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t<number_t<int>> result;
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
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_lhs_rhs_sub() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t<number_t<int>> result;
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
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_lhs_rhs_mul() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t<number_t<int>> result;
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
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_lhs_rhs_div() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a{ 2,3 };
	rational_t<number_t<int>> b{ 3,4 };
	int c{ 1 };
	int d{ 2 };
	rational_t<number_t<int>> result;
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
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
//exception
void test_div_by_zero_exc() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a;
	rational_t<number_t<int>> b{ 0 };
	rational_t<number_t<int>> c;
	std::cout << "\nSource1: ";
	a.print();
	std::cout << "\nSource2: ";
	std::cout << b;
	std::cout << "\nExpected output: Exception!.\n" << "Actual output:\n";
	try
	{
		c = a / b;
	}
	catch (const DivideByZeroError& e)
	{
		std::cout << e.what();
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
void test_scan() {
	std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
	rational_t<number_t<int>> a;
	rational_t<number_t<int>> b;
	std::cout << "\nStringstream input:\n";
	std::string tmp = "2 3";
	std::cout << "\nExpected output:" << tmp;
	std::istringstream iss(tmp);
	try
	{
		a.scan(iss, b);
		std::cout << "\nActual output:";
		b.print();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\nScan error.\n";
	}
	std::cout << "\nif_success:" << EXIT_SUCCESS;
}
#pragma endregion



