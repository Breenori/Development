#include "test.h"

void test_aufbau(){

	cout << "Test aufbau (aus uebung uebernommen\n";

	StNodeOp<double>* root = new StNodeOp<double>(StNodeOp<double>::ADD);

	StNodeValue<double>* left = new StNodeValue<double>(17.0);
	StNodeIdent<double>* right = new StNodeIdent<double>("mehh");

	root->set_left(left);
	root->set_right(right);

	SyntaxTree<double>* st = new SyntaxTree<double>(root);
	NameList<SyntaxTree<double>*>* nl = new NameListMap<SyntaxTree<double>*>();

	StNodeValue<double>* x_value = new StNodeValue<double>(4);
	SyntaxTree<double>* x_tree = new SyntaxTree<double>(x_value);

	nl->register_var("mehh", x_tree);

	cout << "Addition: \n";

	cout << st << "\nResult = " << st->evaluate(nl) << "\n";
	st->print_2d(cout);
	cout << "\n\n";
	st->print_2d_upright(cout);

}

void test_1() {

	cout << "Test 1\n";
	//test from task

	string test;
	ParseSyntaxTree p;

	try {

		p.parse("test.txt");
		p.print_vars(cout);

	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (EvaluationException& e) {
		cout << e.what() << "\n";
	}

	catch (VariableNotFoundException& e) {
		cout << e.what() << "\n";
	}

}

void test_2() {

	cout << "Test 2\n";
	//test nonsense

	string test;
	ParseSyntaxTree p;

	try {

		p.parse("test1.txt");
		p.print_vars(cout);

	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (EvaluationException& e) {
		cout << e.what() << "\n";
	}

	catch (VariableNotFoundException& e) {
		cout << e.what() << "\n";
	}

}

void test_3() {

	cout << "Test 3\n";
	//test empty

	string test;
	ParseSyntaxTree p;

	try {

		p.parse("empty.txt");
		p.print_vars(cout);

	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (EvaluationException& e) {
		cout << e.what() << "\n";
	}

	catch (VariableNotFoundException& e) {
		cout << e.what() << "\n";
	}

}

void test_4() {

	cout << "Test 4\n";
	//test operator

	string test;
	ParseSyntaxTree p;

	try {

		p.parse("test2.txt");

	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (EvaluationException& e) {
		cout << e.what() << "\n";
	}

	catch (VariableNotFoundException& e) {
		cout << e.what() << "\n";
	}

}