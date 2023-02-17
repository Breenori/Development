#include "scanner.h"
#include "arithmetic_parser_.h"
#include <istream>


int main() {
	ArithmeticParser p;
	std::cout << "Input:";
	double value=p.parse(std::cin);
	//Test 1: 2+2=
	//Test2: 1+2+3-4=
	//Test3: -4+3-2=
	//Test4: 3*4=
	//Test5: -4*3*3=
	//Test6: 2/1=
	//Test7: -6/5/-5=
	//Test8: 3+++3=
	//Test9: *3=
	//Test10: 4(3*3=
	std::cout << "Output:" << value;
	return 0;
}