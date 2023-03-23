#include "test.h"
#include "syntax_tree.h"
#include <iostream>
#include "Parser.h"


using namespace xpr;

int main() {
	basic_function_test();

	//----------------------------------------------
	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::ADD);
	StNodeValue<double>* left = new StNodeValue<double>(17.0);
	StNodeValue<double>* right = new StNodeValue<double>(4.0);

	root->set_left(left);
	root->set_right(right);

	SyntaxTree<double>* st = new SyntaxTree<double>(root);

	std::cout << "Addition: \n";
	//std::cout << st << "\n";

	NameList<SyntaxTree<double>*>* nl = new NameListMap<SyntaxTree<double>*>();
	StNodeValue<double>* x_value = new StNodeValue<double>(4);
	SyntaxTree<double>* x_tree = new SyntaxTree<double>(x_value);

	nl->register_var("x", x_tree);
	//SyntaxTree<double>* st = new SyntaxTree<double>(root);
	std::cout << st << "\nResult:" << " = " << root->evaluate(nl) << "\n";

	return 0;

}
