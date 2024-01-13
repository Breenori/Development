#include "rational.h"
#include "test_rational.h"

int main() {
	/*test_constructor1();
	test_constructor2();
	test_constructor3();
	test_constructor3_invalid_input();
	test_copy_constructor();

	test_normalize();

	test_scan();
	test_scan();
	test_scan();

	test_get_numerator();
	test_get_denominator();

	rational_t rat(3, 4);
	rational_t rat2(-3, 4);
	rational_t rat3(3, -4);
	rational_t rat4(-3, -4);
	test_is_negative(rat);
	test_is_negative(rat2);
	test_is_negative(rat3);
	test_is_negative(rat4);
	test_is_positive(rat);
	test_is_positive(rat2);
	test_is_positive(rat3);
	test_is_positive(rat4);
	rational_t rat5(0, 5);
	test_is_zero(rat);
	test_is_zero(rat5);

	test_add();
	test_sub();
	test_mul();
	test_div();*/

	test_write_to_stream();
	test_read_from_stream();
	return 0;
}