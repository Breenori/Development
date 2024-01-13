
#include "rational_test.h"
#include "operations_nelms_test.h"
#include "number_t.h"

#include <iostream>

using std::cout;

int main()
{

	cout << "Testing requirements of point one:\n";
	cout << "int tests:\n";

	rational_test<int>::get_instance().test_rational("Testing rational default parameter for template(1);\nconversion constructor"
		, { 1 }, rational_test<int>::test_int_constr, 1);
	rational_test<int>::get_instance().test_rational("Testing rational default parameter for template(1);\nconstructor for standard values"
		, { 1,2 }, rational_test<int>::test_int_constr_rat, 1, 2);
	rational_test<int>::get_instance().test_rational("Testing rational default parameter for template(1);\ndefault constructor"
		, { 1,1 }, rational_test<int>::test_int_constr_default);


	cout << "Testing requirements of point two:\n";
	cout << "double tests:\n";

	rational_test<double>::get_instance().test_rational("Testing rational init with type double(2);\nconversion constructor"
		, { 1.0 }, rational_test<double>::test_constr, 1.0);
	rational_test<double>::get_instance().test_rational("Testing rational init with type double(2);\nconstructor for standard values"
		, { 1.0,2.0 }, rational_test<double>::test_constr_rat, 1.0, 2.0);
	rational_test<double>::get_instance().test_rational("Testing rational init with type double(2);\ndefault constructor"
		, { 1.0,1.0 }, rational_test<double>::test_constr_default);

	cout << "number_t<int> tests:\n";
	rational_test<number_t<int>>::get_instance().test_rational("Testing rational init with type number_t<int>(2);\nconversion constructor"
		, { 1 }, rational_test<number_t<int>>::test_constr, 1);
	rational_test<number_t<int>>::get_instance().test_rational("Testing rational init with type number_t<int>(2);\nconstructor for standard values"
		, { 1,2 }, rational_test<number_t<int>>::test_constr_rat, 1, 2);
	rational_test<number_t<int>>::get_instance().test_rational("Testing rational init with type number_t<int>(2);\ndefault constructor"
		, { 1,1 }, rational_test<number_t<int>>::test_constr_default);

	// Test concept 
	//rational_t<std::string> test;

	cout << "Testing requirements of point four:\n";
	cout << "Testing arithmetics of rational:\n";
	cout << "int tests:\n";

	rational_test<int>::get_instance().test_rational("Test arithmetics of rationals with type int(4);\naddition"
		, { 1,2 }, { 3,2 }, { 2 }, rational_test<int>::test_add);
	rational_test<int>::get_instance().test_rational("Test arithmetics of rationals with type int(4);\nsubtraction"
		, { 1,2 }, { 3,2 }, { -1 }, rational_test<int>::test_sub);
	rational_test<int>::get_instance().test_rational("Test arithmetics of rationals with type int(4);\nmultiplication"
		, { 1,2 }, { 3,2 }, { 3,4 }, rational_test<int>::test_mul);
	rational_test<int>::get_instance().test_rational("Test arithmetics of rationals with type int(4);\ndivision"
		, { 1,2 }, { 3,2 }, { 2,6 }, rational_test<int>::test_div);

	cout << "double tests:\n";
	rational_test<double>::get_instance().test_rational("Test arithmetics of rationals with type double(4);\naddition"
		, { 1.0,2.0 }, { 3.0,2.0 }, { 2.0 }, rational_test<double>::test_add);
	rational_test<double>::get_instance().test_rational("Test arithmetics of rationals with type double(4);\nsubtraction"
		, { 1.0,2.0 }, { 3.0,2.0 }, { -1.0 }, rational_test<double>::test_sub);
	rational_test<double>::get_instance().test_rational("Test arithmetics of rationals with type double(4);\nmultiplication"
		, { 1.0,2.0 }, { 3.0,2.0 }, { 3.0,4.0 }, rational_test<double>::test_mul);
	rational_test<double>::get_instance().test_rational("Test arithmetics of rationals with type double(4);\ndivision"
		, { 1.0,2.0 }, { 3.0,2.0 }, { 2.0,6.0 }, rational_test<double>::test_div);


	cout << "number_t<int> tests:\n";
	rational_test<number_t<int>>::get_instance().test_rational("Test arithmetics of rationals with type number_t<int>(4);\n addition"
		, { 1,2 }, { 3,2 }, { 2 }, rational_test<number_t<int>>::test_add);
	rational_test<number_t<int>>::get_instance().test_rational("Test arithmetics of rationals with type number_t<int>(4);\n subtraction"
		, { 1,2 }, { 3,2 }, { -1 }, rational_test<number_t<int>>::test_sub);
	rational_test<number_t<int>>::get_instance().test_rational("Test arithmetics of rationals with type number_t<int>(4);\n multiplication"
		, { 1,2 }, { 3,2 }, { 3,4 }, rational_test<number_t<int>>::test_mul);
	rational_test<number_t<int>>::get_instance().test_rational("Test arithmetics of rationals with type number_t<int>(4);\n division"
		, { 1,2 }, { 3,2 }, { 2,6 }, rational_test<number_t<int>>::test_div);

	cout << "Testing comparisons of rational(== will not be tested as it is used in almost all functions):\n";
	cout << "int tests:\n";

	rational_test<int>::get_instance().test_rational("Test comparison != with type int(4);\ntwo not identical numbers"
		, { 1,2 }, { 2,1 }, true, rational_test<int>::test_not_equal);
	rational_test<int>::get_instance().test_rational("Test comparison != with type int(4);\ntwo  identical numbers"
		, { 1,2 }, { 1,2 }, false, rational_test<int>::test_not_equal);
	rational_test<int>::get_instance().test_rational("Test comparison < with type int(4);\nn1<n2"
		, { 1,2 }, { 2,1 }, true, rational_test<int>::test_smaller);
	rational_test<int>::get_instance().test_rational("Test comparison < with type int(4);\nn1>=n2"
		, { 2,1 }, { 1,2 }, false, rational_test<int>::test_smaller);
	rational_test<int>::get_instance().test_rational("Test comparison > with type int(4);\nn1>n2"
		, { 2,1 }, { 1,2 }, true, rational_test<int>::test_bigger);
	rational_test<int>::get_instance().test_rational("Test comparison > with type int(4);\nn1<=n2"
		, { 1,2 }, { 2,1 }, false, rational_test<int>::test_bigger);
	rational_test<int>::get_instance().test_rational("Test comparison <= with type int(4);\nn1<=n2"
		, { 2,1 }, { 2,1 }, true, rational_test<int>::test_smaller_equal);
	rational_test<int>::get_instance().test_rational("Test comparison <= with type int(4);\nn1>n2"
		, { 2,1 }, { 1,2 }, false, rational_test<int>::test_smaller_equal);
	rational_test<int>::get_instance().test_rational("Test comparison >= with type int(4);\nn1>=n2"
		, { 1,2 }, { 1,2 }, true, rational_test<int>::test_bigger_equal);
	rational_test<int>::get_instance().test_rational("Test comparison >= with type int(4);\nn1<n2"
		, { 1,2 }, { 2,1 }, false, rational_test<int>::test_bigger_equal);

	cout << "double tests:\n";

	rational_test<double>::get_instance().test_rational("Test comparison != with type double(4);\ntwo not identical numbers"
		, { 1,2 }, { 2,1 }, true, rational_test<double>::test_not_equal);
	rational_test<double>::get_instance().test_rational("Test comparison != with type double(4);\ntwo  identical numbers"
		, { 1,2 }, { 1,2 }, false, rational_test<double>::test_not_equal);
	rational_test<double>::get_instance().test_rational("Test comparison < with type double(4);\nn1<n2"
		, { 1,2 }, { 2,1 }, true, rational_test<double>::test_smaller);
	rational_test<double>::get_instance().test_rational("Test comparison < with type double(4);\nn1>=n2"
		, { 2,1 }, { 1,2 }, false, rational_test<double>::test_smaller);
	rational_test<double>::get_instance().test_rational("Test comparison > with type double(4);\nn1>n2"
		, { 2,1 }, { 1,2 }, true, rational_test<double>::test_bigger);
	rational_test<double>::get_instance().test_rational("Test comparison > with type double(4);\nn1<=n2"
		, { 1,2 }, { 2,1 }, false, rational_test<double>::test_bigger);
	rational_test<double>::get_instance().test_rational("Test comparison <= with type double(4);\nn1<=n2"
		, { 2,1 }, { 2,1 }, true, rational_test<double>::test_smaller_equal);
	rational_test<double>::get_instance().test_rational("Test comparison <= with type double(4);\nn1>n2"
		, { 2,1 }, { 1,2 }, false, rational_test<double>::test_smaller_equal);
	rational_test<double>::get_instance().test_rational("Test comparison >= with type double(4);\nn1>=n2"
		, { 1,2 }, { 1,2 }, true, rational_test<double>::test_bigger_equal);
	rational_test<double>::get_instance().test_rational("Test comparison >= with type double(4);\nn1<n2"
		, { 1,2 }, { 2,1 }, false, rational_test<double>::test_bigger_equal);

	cout << "number_t<int> tests:\n";

	rational_test<number_t<int>>::get_instance().test_rational("Test comparison != with type number_t<int>(4);\ntwo not identical numbers"
		, { 1,2 }, { 2,1 }, true, rational_test<number_t<int>>::test_not_equal);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison != with type number_t<int>(4);\ntwo  identical numbers"
		, { 1,2 }, { 1,2 }, false, rational_test<number_t<int>>::test_not_equal);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison < with type number_t<int>(4);\nn1<n2"
		, { 1,2 }, { 2,1 }, true, rational_test<number_t<int>>::test_smaller);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison < with type number_t<int>(4);\nn1>=n2"
		, { 2,1 }, { 1,2 }, false, rational_test<number_t<int>>::test_smaller);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison > with type number_t<int>(4);\nn1>n2"
		, { 2,1 }, { 1,2 }, true, rational_test<number_t<int>>::test_bigger);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison > with type number_t<int>(4);\nn1<=n2"
		, { 1,2 }, { 2,1 }, false, rational_test<number_t<int>>::test_bigger);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison <= with type number_t<int>(4);\nn1<=n2"
		, { 2,1 }, { 2,1 }, true, rational_test<number_t<int>>::test_smaller_equal);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison <= with type number_t<int>(4);\nn1>n2"
		, { 2,1 }, { 1,2 }, false, rational_test<number_t<int>>::test_smaller_equal);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison >= with type number_t<int>(4);\nn1>=n2"
		, { 1,2 }, { 1,2 }, true, rational_test<number_t<int>>::test_bigger_equal);
	rational_test<number_t<int>>::get_instance().test_rational("Test comparison >= with type number_t<int>(4);\nn1<n2"
		, { 1,2 }, { 2,1 }, false, rational_test<number_t<int>>::test_bigger_equal);

	cout << "Testing >> of rational(<< will not be tested as it is used in almost all functions):\n";
	cout << "int tests:\n";

	rational_test<int>::get_instance().test_scan("Test scan of rational<T> with type int(4)"
		, "2 3", { 2,3 });
	rational_test<int>::get_instance().test_scan("Test scan of rational<T> with type int(4)\ntest failed read"
		, "", { 1,1 });

	cout << "double tests:\n";

	rational_test<double>::get_instance().test_scan("Test scan of rational<T> with type double(4)"
		, "2 3", { 2,3 });
	rational_test<double>::get_instance().test_scan("Test scan of rational<T> with type double(4)\ntest failed read"
		, "", { 1,1 });

	cout << "number_t<int> tests:\n";

	rational_test<number_t<int>>::get_instance().test_scan("Test scan of rational<T> with type number_t<int>(4)"
		, "2 3", { 2,3 });
	rational_test<number_t<int>>::get_instance().test_scan("Test scan of rational<T> with type number_t<int>(4)\ntest failed read"
		, "", { 1,1 });


	cout << "Testing requirements of point five and seven:\n";
	cout << "Testing operations:\n";
	cout << "int tests:\n";
	operations_test<int>::get_instance().test_operations("Test operation equals with type int(5,7)\nequal numbers"
		, 1, 1, true, operations_test<int>::test_equals);
	operations_test<int>::get_instance().test_operations("Test operation equals with type int(5,7)\nnon equal numbers"
		, 1, 2, false, operations_test<int>::test_equals);
	operations_test<int>::get_instance().test_operations("Test operation divides with type int(5,7)\nn2 divides n1"
		, 2, 1, true, operations_test<int>::test_divides);
	operations_test<int>::get_instance().test_operations("Test operation divides with type int(5,7)\nn2 does not divide n1"
		, 1, 2, false, operations_test<int>::test_divides);

	operations_test<int>::get_instance().test_operations("Test operation is_negative with type int(5,7)\nnegative number"
		, -1, true, operations_test<int>::test_is_negative);
	operations_test<int>::get_instance().test_operations("Test operation is_negative with type int(5,7)\nnon-negative number"
		, 1, false, operations_test<int>::test_is_negative);

	operations_test<int>::get_instance().test_operations("Test operation is_zero with type int(5,7)"
		, 0, true, operations_test<int>::test_is_zero);
	operations_test<int>::get_instance().test_operations("Test operation is_zero with type int(5,7)"
		, 1, false, operations_test<int>::test_is_zero);

	operations_test<int>::get_instance().test_operations("Test operation negate with type int(5,7)",
		-5, 5, operations_test<int>::test_negate);

	operations_test<int>::get_instance().test_operations("Test operation gcd with type int(5,7)"
		, 8, 4, 4, operations_test<int>::test_gcd);
	operations_test<int>::get_instance().test_operations("Test operation remainder with type int(5,7)"
		, 8, 4, 0, operations_test<int>::test_remainder);


	cout << "double tests:\n";
	operations_test<double>::get_instance().test_operations("Test operation equals with type double(5,7)\nequal numbers"
		, 1.0, 1.0, true, operations_test<double>::test_equals);
	operations_test<double>::get_instance().test_operations("Test operation equals with type double(5,7)\nnon equal numbers"
		, 1.0, 2.0, false, operations_test<double>::test_equals);
	operations_test<double>::get_instance().test_operations("Test operation divides with type double(5,7)\nn2 divides n1"
		, 2.0, 1.0, true, operations_test<double>::test_divides);
	operations_test<double>::get_instance().test_operations("Test operation divides with type double(5,7)\nn2 does not divide n1"
		, 1.0, 2.0, false, operations_test<double>::test_divides);

	operations_test<double>::get_instance().test_operations("Test operation is_negative with type double(5,7)\nnegative number"
		, -1.0, true, operations_test<double>::test_is_negative);
	operations_test<double>::get_instance().test_operations("Test operation is_negative with type double(5,7)\nnon-negative number"
		, 1.0, false, operations_test<double>::test_is_negative);

	operations_test<double>::get_instance().test_operations("Test operation is_zero with type double(5,7)"
		, 0.0, true, operations_test<double>::test_is_zero);
	operations_test<double>::get_instance().test_operations("Test operation is_zero with type double(5,7)"
		, 1.0, false, operations_test<double>::test_is_zero);

	operations_test<double>::get_instance().test_operations("Test operation negate with type double(5,7)",
		-5.0, 5.0, operations_test<double>::test_negate);

	operations_test<double>::get_instance().test_operations("Test operation gcd with type double(5,7)"
		, 8.0, 4.0, 4.0, operations_test<double>::test_gcd);
	operations_test<double>::get_instance().test_operations("Test operation remainder with type double(5,7)"
		, 8.0, 4.0, 0.0, operations_test<double>::test_remainder);


	cout << "number_t<int> tests:\n";
	operations_test<number_t<int>>::get_instance().test_operations("Test operation equals with type number_t<int>(5,7)\nequal numbers"
		, 1, 1, true, operations_test<number_t<int>>::test_equals);
	operations_test<number_t<int>>::get_instance().test_operations("Test operation equals with type number_t<int>(5,7)\nnon equal numbers"
		, 1, 2, false, operations_test<number_t<int>>::test_equals);
	operations_test<number_t<int>>::get_instance().test_operations("Test operation divides with type number_t<int>(5,7)\nn2 divides n1"
		, 2, 1, true, operations_test<number_t<int>>::test_divides);
	operations_test<number_t<int>>::get_instance().test_operations("Test operation divides with type number_t<int>(5,7)\nn2 does not divide n1"
		, 1, 2, false, operations_test<number_t<int>>::test_divides);

	operations_test<number_t<int>>::get_instance().test_operations("Test operation is_negative with type number_t<int>(5,7)\nnegative number"
		, -1, true, operations_test<number_t<int>>::test_is_negative);
	operations_test<number_t<int>>::get_instance().test_operations("Test operation is_negative with type number_t<int>(5,7)\nnon-negative number"
		, 1, false, operations_test<number_t<int>>::test_is_negative);

	operations_test<number_t<int>>::get_instance().test_operations("Test operation is_zero with type number_t<int>(5,7)"
		, 0, true, operations_test<number_t<int>>::test_is_zero);
	operations_test<number_t<int>>::get_instance().test_operations("Test operation is_zero with type number_t<int>(5,7)"
		, 1, false, operations_test<number_t<int>>::test_is_zero);

	operations_test<number_t<int>>::get_instance().test_operations("Test operation negate with type number_t<int>(5,7)",
		-5, 5, operations_test<number_t<int>>::test_negate);

	operations_test<number_t<int>>::get_instance().test_operations("Test operation gcd with type number_t<int>(5,7)"
		, 8, 4, 4, operations_test<number_t<int>>::test_gcd);
	operations_test<number_t<int>>::get_instance().test_operations("Test operation remainder with type number_t<int>(5,7)"
		, 8, 4, 0, operations_test<number_t<int>>::test_remainder);

	cout << "Testing requirements of point six:\n";
	cout << "Testing nelms:\n";
	cout << "int tests:\n";

	nelms_test<int>::get_instance().test_one("Test zero-element of type int(6)", 1);
	nelms_test<int>::get_instance().test_zero("Test zero-element of type int(6)", 0);

	cout << "double tests:\n";

	nelms_test<double>::get_instance().test_one("Test zero-element of type double(6)", 1.0);
	nelms_test<double>::get_instance().test_zero("Test zero-element of type double(6)", 0.0);

	cout << "number_t<int> tests:\n";

	nelms_test<number_t<int>>::get_instance().test_one("Test zero-element of type number_t<int>(6)", number_t<int>(1));
	nelms_test<number_t<int>>::get_instance().test_zero("Test zero-element of type number_t<int>(6)", number_t<int>(0));


	cout << "Testing requirements of point eight:\n";
	cout << "Testing invert:\n";
	cout << "int tests:\n";

	rational_test<int>::get_instance().test_inverse("Test inverse of type int(8)"
		, { 3,4 }, { 4,3 });
	rational_test<int>::get_instance().test_inverse("Test inverse of type int(8)\ndivision by zero occurs"
		, { 0,4 }, { 0,4 });

	cout << "double tests:\n";

	rational_test<double>::get_instance().test_inverse("Test inverse of type double(8)"
		, { 3.0,4.0 }, { 4.0,3.0 });
	rational_test<double>::get_instance().test_inverse("Test inverse of type double(8)\ndivision by zero occurs"
		, { 0.0,4.0 }, { 0.0,4.0 });

	cout << "number_t<int> tests:\n";

	rational_test<number_t<int>>::get_instance().test_inverse("Test inverse of type number_t<int>(8)"
		, { number_t<int>(3), number_t<int>(4) }, { number_t<int>(4),(3) });
	rational_test<number_t<int>>::get_instance().test_inverse("Test inverse of type number_t<int>(8)\ndivision by zero occurs"
		, { number_t<int>(0),number_t<int>(4) }, { number_t<int>(0),(4) });
}

