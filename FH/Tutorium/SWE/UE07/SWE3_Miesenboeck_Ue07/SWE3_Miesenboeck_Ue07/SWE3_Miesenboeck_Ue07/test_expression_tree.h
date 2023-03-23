#pragma once
#include "parse_syntax_tree.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

class test_expression_tree
{
public:
	void static test_e_t(string const& expr, string const exp_res, size_t const test_no, string const& test_txt);
	void static test_e_t_multi(vector<string> const& expr_vec, vector<string> const exp_res_vec, size_t const test_no, string const& test_txt);
	void static test_e_t_excp(string const& expr, size_t const test_no, string const& test_txt);
	void static test_undef();
private:
};

