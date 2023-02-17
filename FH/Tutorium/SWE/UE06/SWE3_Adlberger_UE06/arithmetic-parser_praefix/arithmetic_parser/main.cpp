#include "scanner.h"
#include "arithmetic_parser_.h"


int main() {
	ArithmeticParser p;
	std::cout << "input:";
	std::cout<<p.parse(std::cin);

	return 0;
}