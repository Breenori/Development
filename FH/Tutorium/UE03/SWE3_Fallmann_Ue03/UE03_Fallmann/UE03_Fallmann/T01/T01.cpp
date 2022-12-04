#include <iostream>

#include "rational_test.h"

using std::cout;

int main()
{
	cout << "Test01:\nTesting creation of invalid rational\n";
	cout << (rational_test::test_invalid_rational() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test02:\nTesting division by zero\n";
	cout << (rational_test::test_invalid_division() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test03:\nTesting normalisation of neg. numerator and denominator and addition of zero\n";
	cout << (rational_test::test_negative_normalize_and_add_of_zero() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test04:\nTesting normalisation of normalized rational and multiplication of zero\n";
	cout << (rational_test::test_normalized_and_mul_of_zero() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test05:\nTesting normalisation of non normalized rational nr and subtraction of zero\n";
	cout << (rational_test::test_non_normalized_and_sub_of_zero() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test06:\nTesting print of whole number\n";
	rational_test::test_whole_nr_print();
	cout << std::endl;
	cout << std::endl;

	cout << "Test07:\nTesting print of rational number\n";
	rational_test::test_rat_nr_print();
	cout << std::endl;
	cout << std::endl;

	cout << "Test08:\nTesting scan of whole number\n";
	cout << (rational_test::test_whole_nr_scan ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test09:\nTesting scan of rational number\n";
	cout << (rational_test::test_whole_nr_scan ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test10:\nTesting scan of invalid file\n";
	cout << (rational_test::test_whole_nr_scan ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test11:\nTesting default constructor\n";
	cout << (rational_test::test_default_init() ?
		"\nsuccess\n" : "\nfailure\n");
	cout << std::endl;

	cout << "Test12:\nTesting int constructor\n";
	cout << (rational_test::test_int_init() ?
		"\nsuccess\n" : "\nfailure\n");
	cout << std::endl;

	cout << "Test13:\nTesting constructor init with two numbers\n";
	cout << (rational_test::test_rat_init() ?
		"\nsuccess\n" : "\nfailure\n");
	cout << std::endl;

	cout << "Test14:\nTesting copy constructor\n";
	cout << (rational_test::test_copy_init() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test15:\nTesting >= positive\n";
	cout << (rational_test::test_ge_pos() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test16:\nTesting >= negative\n";
	cout << (rational_test::test_ge_neg() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test17:\nTesting != positive\n";
	cout << (rational_test::test_ne_pos() ?
		"success\n" : "failure\n");
	cout << std::endl;


	cout << "Test18:\nTesting != negative\n";
	cout << (rational_test::test_ne_neg() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test19:\nTesting == positive\n";
	cout << (rational_test::test_eq_pos() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test20:\nTesting == negative\n";
	cout << (rational_test::test_eq_neg() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test21:\nTesting < pos\n";
	cout << (rational_test::test_s_pos() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test22:\nTesting < negative\n";
	cout << (rational_test::test_s_neg() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test23:\nTesting > positive\n";
	cout << (rational_test::test_g_pos() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test24:\nTesting > negative\n";
	cout << (rational_test::test_g_neg() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test25:\nTesting <= positive\n";
	cout << (rational_test::test_se_pos() ?
		"success\n" : "failure\n");
	cout << std::endl;


	cout << "Test26:\nTesting <= negative\n";
	cout << (rational_test::test_se_neg() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test27:\nTesting compound assignment operator +=\n";
	cout << (rational_test::test_comp_ass_add() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test28:\nTesting compound assignment operator -=\n";
	cout << (rational_test::test_comp_ass_sub() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test29:\nTesting compound assignment operator *=\n";
	cout << (rational_test::test_comp_ass_mul() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test30:\nTesting compound assignment operator /=\n";
	cout << (rational_test::test_comp_ass_div() ?
		"success\n" : "failure\n");
	cout << std::endl;
	
	cout << "Test31:\nTesting integer-operation add\n";
	cout << (rational_test::test_add() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test32:\nTesting integer-operation subtract\n";
	cout << (rational_test::test_sub() ?
		"success\n" : "failure\n");
	cout << std::endl;

	cout << "Test33:\nTesting integer-operation multiply\n";
	cout << (rational_test::test_mul() ?
		"success\n" : "failure\n");
	cout << std::endl;


	cout << "Test34:\nTesting integer-operation divide\n";
	cout << (rational_test::test_div() ?
		"success\n" : "failure\n");
	cout << std::endl;
}