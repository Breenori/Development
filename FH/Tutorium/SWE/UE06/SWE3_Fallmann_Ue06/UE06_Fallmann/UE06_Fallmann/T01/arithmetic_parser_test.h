#pragma once

#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include <fstream>

#include "arithmetic_parser.h"

using std::cout;
using std::string;


double test_arith(std::istream& in);

void run_test(std::istream& in,std::string const& description, double expected_result);

void run_test_sstream(std::string in,std::string const& description, double expected_result);

void run_neg_test(std::string in,std::string const& description);

void test_inv_file();
void test_working_file();
void test_simple_expr();
void test_neg_nrs();
void test_p_expr();
void test_mult_div();
void test_add_sub();

void neg_test_simple_expr();
void neg_test_term();
void neg_test_mult_div();
void neg_test_div_by_zero();
