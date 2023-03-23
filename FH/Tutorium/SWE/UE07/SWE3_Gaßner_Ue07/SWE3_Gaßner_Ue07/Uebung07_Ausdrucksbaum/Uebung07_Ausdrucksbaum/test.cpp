#include "test.h"
#include <iostream>
#include <fstream>
using namespace xpr;


void test_evaluate_add() {
	std::cout << "TESTING EVALUATE ADD:\n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::ADD);
	StNodeValue<double>* left = new StNodeValue<double>(13.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("x");

	root->set_left(left);
	root->set_right(right);

	std::cout << "\nRoot: ";
	root->print(std::cout);
	std::cout << "\nleft Node: ";
	left->print(std::cout);
	std::cout << "\nright Node: ";
	right->print(std::cout);

	NameList<SyntaxTree<double>*>* name_list = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* val = new StNodeValue<double>(8);
	SyntaxTree<double>* tree = new SyntaxTree<double>(val);

	std::cout << "\nvalue for x: ";
	val->print(std::cout);
	std::cout << "\n";

	SyntaxTree<double>* syntax_tree = new SyntaxTree<double>(root);

	name_list->register_var("x", tree);

	std::cout << syntax_tree << "=" << root->evaluate(name_list) << "\n";
}

void test_evaluate_sub() {
	std::cout << "TESTING EVALUATE SUB:\n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::SUB);
	StNodeValue<double>* left = new StNodeValue<double>(13.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("x");

	root->set_left(left);
	root->set_right(right);

	std::cout << "\nRoot: ";
	root->print(std::cout);
	std::cout << "\nleft Node: ";
	left->print(std::cout);
	std::cout << "\nright Node: ";
	right->print(std::cout);

	NameList<SyntaxTree<double>*>* name_list = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* val = new StNodeValue<double>(8);
	SyntaxTree<double>* tree = new SyntaxTree<double>(val);

	std::cout << "\nvalue for x: ";
	val->print(std::cout);
	std::cout << "\n";

	SyntaxTree<double>* syntax_tree = new SyntaxTree<double>(root);

	name_list->register_var("x", tree);

	std::cout << syntax_tree << "=" << root->evaluate(name_list) << "\n";
}

void test_evaluate_mul() {
	std::cout << "TESTING EVALUATE MUL:\n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::MUL);
	StNodeValue<double>* left = new StNodeValue<double>(13.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("x");

	root->set_left(left);
	root->set_right(right);

	std::cout << "\nRoot: ";
	root->print(std::cout);
	std::cout << "\nleft Node: ";
	left->print(std::cout);
	std::cout << "\nright Node: ";
	right->print(std::cout);


	NameList<SyntaxTree<double>*>* name_list = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* val = new StNodeValue<double>(8);
	SyntaxTree<double>* tree = new SyntaxTree<double>(val);

	std::cout << "\nvalue for x: ";
	val->print(std::cout);
	std::cout << "\n";

	SyntaxTree<double>* syntax_tree = new SyntaxTree<double>(root);

	name_list->register_var("x", tree);

	std::cout << syntax_tree << "=" << root->evaluate(name_list) << "\n";
}

void test_evaluate_div() {
	std::cout << "TESTING EVALUATE DIV:\n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::DIV);
	StNodeValue<double>* left = new StNodeValue<double>(13.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("x");

	root->set_left(left);
	root->set_right(right);

	std::cout << "\nRoot: ";
	root->print(std::cout);
	std::cout << "\nleft Node: ";
	left->print(std::cout);
	std::cout << "\nright Node: ";
	right->print(std::cout);

	NameList<SyntaxTree<double>*>* name_list = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* val = new StNodeValue<double>(8);
	SyntaxTree<double>* tree = new SyntaxTree<double>(val);

	std::cout << "\nvalue for x: ";
	val->print(std::cout);
	std::cout << "\n";

	SyntaxTree<double>* syntax_tree = new SyntaxTree<double>(root);

	name_list->register_var("x", tree);

	std::cout << syntax_tree << "=" << root->evaluate(name_list) << "\n";
}

void test_evaluate_exp() {
	std::cout << "TESTING EVALUATE EXP:\n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::EXP);
	StNodeValue<double>* left = new StNodeValue<double>(13.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("x");

	root->set_left(left);
	root->set_right(right);

	std::cout << "\nRoot: ";
	root->print(std::cout);
	std::cout << "\nleft Node: ";
	left->print(std::cout);
	std::cout << "\nright Node: ";
	right->print(std::cout);

	NameList<SyntaxTree<double>*>* name_list = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* val = new StNodeValue<double>(8);
	SyntaxTree<double>* tree = new SyntaxTree<double>(val);

	std::cout << "\nvalue for x: ";
	val->print(std::cout);
	std::cout << "\n";

	SyntaxTree<double>* syntax_tree = new SyntaxTree<double>(root);

	name_list->register_var("x", tree);

	std::cout << syntax_tree << "=" << root->evaluate(name_list) << "\n";
}

void test_print_tree() {
	std::cout << "TESTING PRINT TREE:\n";

	StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::MUL); // Operator knoten
	StNodeValue<double>* right = new StNodeValue<double>(13.0);
	StNodeIdent<double>* left = new StNodeIdent<double>("y");

	StNodeOperator<double>* root2 = new StNodeOperator<double>(StNodeOperator<double>::SUB); // Operator knoten
	StNodeValue<double>* right2 = new StNodeValue<double>(8);

	root->set_left(right);
	root->set_right(left);

	root2->set_right(root);
	root2->set_left(right2);


	NameList<SyntaxTree<double>*>* name_list = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* val = new StNodeValue<double>(6);
	SyntaxTree<double>* tree = new SyntaxTree<double>(val);

	SyntaxTree<double>* syntax_tree = new SyntaxTree<double>(root2);

	name_list->register_var("y", tree);

	std::cout << "\nRoot: ";
	root->print(std::cout);
	std::cout << "\nsecond Root: ";
	root2->print(std::cout);
	std::cout << "\nleft Node: ";
	left->print(std::cout);
	std::cout << "\nright Node: ";
	right->print(std::cout);
	std::cout << "\nsecond right Node: ";
	right2->print(std::cout);
	std::cout << "\nvalue for y: ";
	val->print(std::cout);
	std::cout << "\n\n";

	std::cout << "Print tree 2d:\n";
	syntax_tree->print_2d(std::cout);
	std::cout << "\n\n\n";
	std::cout << "Print tree 2d_upright:\n";
	syntax_tree->print_2d_upright(std::cout);
	std::cout << "\n\n\n";
	std::cout << "Print name_list:\n";
	name_list->print(std::cout);

}


void test_valid_input() {
	std::cout << "TEST VALID INPUT\n\n";

	ParseSyntaxTree parser = new ParseSyntaxTree<StNode*>();
	std::cout << "Parse set (a, 1);:\n";
	std::string s1{ "set (a, 1);" };
	parser.parse(s1);

	std::cout << "Parse set (pi, 3.1415);\n";
	std::string s2{ "set (pi, 3.1415);" };
	parser.parse(s2);

	std::cout << "Parse set (k, -(a + 3) * pi^0.5);\n";
	std::string s3{ "set (k, -(a + 3) * pi^0.5);" };
	parser.parse(s3);

	std::cout << "Parse set (x, 2)\n";
	std::string s4{ "set (x, 2);" };
	parser.parse(s4);

	std::cout << "print (k);\n";
	std::string s5{ "print (k);" };
	parser.parse(s5);

	std::cout << "Parse print (4 / (2 * (3 -1 )));\n";
	std::string s6{ "print (4 / (2 * (3 -1 )));" };
	parser.parse(s6);

	std::cout << "set (x, y^2 -4);\n";
	std::string s7{ "set (x, y^2 -4);" };
	parser.parse(s7);

	std::cout << "Parse set (y, 5); print (x); print (y); print (x / 2);\n";
	std::string s8{ "set (y, 5); print (x); print (y); print (x / 2);" };
	parser.parse(s8);

	std::cout << "\n\n\n";
	std::cout << "Read from file:\n";
	std::ifstream file{ "file.txt" };
	parser.parse(file);

}

template<typename T>
void test_invalid_input() {
	std::cout << "TEST INVALID INPUT\n\n";

	try {
		ParseSyntaxTree<T> parser;
		std::cout << "Parse set (a, 1);:\n";
		std::string s1{ "HALLO (a, 1);" };
		parser.parse(s1);

		std::cout << "Parse set (pi, 3.1415);\n";
		std::string s2{ "set (pi, 3.1415- - -);" };
		parser.parse(s2);

		std::cout << "Parse set (k, -(a + 3 * pi^0.5;\n";
		std::string s3{ "set (k, -(a + 3 * pi^0.5;" };
		parser.parse(s3);

		std::cout << "Parse set (, 2)\n";
		std::string s4{ "set (, 2);" };
		parser.parse(s4);

		std::cout << "print (+*k-);\n";
		std::string s5{ "print (+*k-);" };
		parser.parse(s5);
	}
	catch (std::exception const& m) {
		std::cerr << m.what() << "\n";
	}

}

template <typename T>
void test_division_by_zero()
{
	std::cout << "TEST DIVISION BY ZERO\n\n";

	try {
		ParseSyntaxTree<T> parser;
		std::cout << "Parse set (a/0);:\n";
		std::string s1{ "set (a/0);" };
		parser.parse(s1);

		std::cout << "Parse set ((pi, 3.1415)/0);\n";
		std::string s2{ "set ((pi, 3.1415)/0);" };
		parser.parse(s2);

		std::cout << "Parse set (k, -(a + 3) / 0);\n";
		std::string s3{ "set (k, -(a + 3) / 0);" };
		parser.parse(s3);
	}
	catch (std::exception const& m) {
		std::cerr << m.what() << "\n";
	}
}


