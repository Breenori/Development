#ifndef TEST_H
#define TEST_H

#include "parser.h"

using namespace xpr;

void test_add_to_namelist(NameListMap<SyntaxTree<double>*>* _name_list_, std::string const& _name_, SyntaxTree<double>* _value_) {

	std::cout << "Testing adding value to namelist...\n";

	std::cout << "Namelist before adding new value: \n";
	_name_list_->print(std::cout);
	_name_list_->register_var(_name_, _value_);
	std::cout << "Namelist after adding new value: \n";
	_name_list_->print(std::cout);

}

void test_lookup_var(NameListMap<SyntaxTree<double>*>* _name_list_, std::string const& _name_) {

	std::cout << "Testing getting value from namelist...\n";

	std::cout << "NameList: \n";
	_name_list_->print(std::cout);

	std::cout << "Value of " << _name_ << ": " << _name_list_->lookup_var(_name_);

}

#endif