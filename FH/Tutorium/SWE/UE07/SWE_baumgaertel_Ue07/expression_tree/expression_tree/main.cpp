#include "syntax_tree.h"
#include "programm_parser.h"
#include <iostream>

using namespace xpr;

void test_print_2d_simple() {
	std::cout << "\ntesting simple trees: \n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::ADD);
	StNodeValue<double>* left = new StNodeValue<double>(17.0);
	StNodeValue<double>* right = new StNodeValue<double>(4.0);
	root->set_left(left);
	root->set_right(right);

	SyntaxTree<double>* st = new SyntaxTree<double>(root);
	std::cout << st << "\n";
	st->print_horizontally();
	st->print_vertically();

	std::cout << "\n---------------------------------------------------------";
}

void test_print_2d_complex() {
	std::cout << "\ntesting more complex trees: \n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::ADD);
	StNodeOperator<double>* left_1 = new StNodeOperator<double>(StNodeOperator<double>::MUL);
	StNodeOperator<double>* right_1 = new StNodeOperator<double>(StNodeOperator<double>::DIV);
	root->set_left(left_1);
	root->set_right(right_1);
	StNodeOperator<double>* left_2 = new StNodeOperator<double>(StNodeOperator<double>::ADD);
	StNodeValue<double>* right_2 = new StNodeValue<double>(3.0);
	left_1->set_left(left_2);
	left_1->set_right(right_2);
	StNodeValue<double>* left_3 = new StNodeValue<double>(2.0);
	StNodeValue<double>* right_3 = new StNodeValue<double>(4.0);
	left_2->set_left(left_3);
	left_2->set_right(right_3);
	StNodeValue<double>* left_4 = new StNodeValue<double>(5.0);
	StNodeValue<double>* right_4 = new StNodeValue<double>(2.0);
	right_1->set_left(left_4);
	right_1->set_right(right_4);

	SyntaxTree<double>* st = new SyntaxTree<double>(root);
	std::cout << st << "\n";
	st->print_horizontally();
	st->print_vertically();

	std::cout << "\n---------------------------------------------------------";
}

void test_namelist() {
	std::cout << "\ntesting usage of namelist: \n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::ADD);
	StNodeValue<double>* left = new StNodeValue<double>(17.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("x");

	root->set_left(left);
	root->set_right(right);


	NameList<SyntaxTree<double>*>* nl = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* x_value = new StNodeValue<double>(3);
	SyntaxTree<double>* x_tree = new SyntaxTree<double>(x_value);

	nl->register_var("x", x_tree);

	SyntaxTree<double>* st = new SyntaxTree<double>(root);
	std::cout << "Addition: \n";
	std::cout << st << "\n";
	std::cout << "Result: " << st->evaluate(nl) << "\n";

	std::cout << "\n---------------------------------------------------------";
}

void test_namelist2() {
	std::cout << "\ntesting more complex of namelist: \n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::ADD);
	StNodeValue<double>* left = new StNodeValue<double>(17.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("x");

	root->set_left(left);
	root->set_right(right);


	NameList<SyntaxTree<double>*>* nl = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* x_value = new StNodeValue<double>((9-2) * 2.5);
	SyntaxTree<double>* x_tree = new SyntaxTree<double>(x_value);

	nl->register_var("x", x_tree);

	SyntaxTree<double>* st = new SyntaxTree<double>(root);
	std::cout << "Addition: \n";
	std::cout << st << "\n";
	std::cout << "Result: " << st->evaluate(nl) << "\n";

	std::cout << "\n---------------------------------------------------------";
}

void main() {
	test_print_2d_simple();
	test_print_2d_complex();
	test_namelist();
	test_namelist2();

	std::cout << "\n";

	std::string expr;
	std::cout << "Type in program expression: ";
	getline(std::cin, expr);
	double value = ProgrammParser().parse(expr);
	if (isinf(value)) {
		throw DivByZeroException("Division by zero.");
	}
	else {
		std::cout << "\nresult: " << value << "\n";
	}
}