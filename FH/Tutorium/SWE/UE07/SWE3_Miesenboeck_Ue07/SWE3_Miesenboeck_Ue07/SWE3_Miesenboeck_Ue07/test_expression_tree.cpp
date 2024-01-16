#include "test_expression_tree.h"

#include <iostream>


using std::cout;
using std::endl;

void test_expression_tree::test_e_t(string const& expr, string const exp_res, size_t const test_no, string const& test_txt)
{
	cout << endl << "TESTFALL " << test_no << ": " << test_txt << endl << endl;

	std::cout << "Evaluating input '" << expr << "' ..." << endl << endl;
	cout << "Expected result: " << exp_res << endl << endl;


	try {
		xpr::parse_syntax_tree pst;
		cout << "Actual result: ";
		pst.parse(expr);
		cout << endl << endl;


		cout << "------- TEST ERFOLGREICH -------" << endl << endl << endl << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	catch (std::exception const& x) {
		std::cerr << "Exception: " << x.what() << endl << endl;
		cout << "-X-X-X- TEST FEHLGESCHLAGEN -X-X-X-" << endl << endl << endl << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
	}

}

void test_expression_tree::test_e_t_multi(vector<string> const& expr_vec, vector<string> const exp_res_vec, size_t const test_no, string const& test_txt)
{
	cout << endl << "TESTFALL " << test_no << ": " << test_txt << endl << endl;
	xpr::parse_syntax_tree pst;


	if (expr_vec.size() == exp_res_vec.size())
	{
		for (int i = 0; i < expr_vec.size(); ++i)
		{
			std::cout << "Evaluating input '" << expr_vec[i] << "' ..." << endl << endl;
			cout << "Expected result: " << exp_res_vec[i] << endl << endl;


			try {
				if (exp_res_vec[i] == "PRINTNAMELIST")
				{
					pst.print_namelist();
					cout << endl << endl;
				}
				else if(exp_res_vec[i] == "PRINTMETHODS")
				{
					pst.print_in_order_by_name(expr_vec[i]);
					cout << endl;
					pst.print_post_order_by_name(expr_vec[i]);
					cout << endl;
					pst.print_pre_order_by_name(expr_vec[i]);
					cout << endl << endl << endl;
					pst.print_2d_by_name(expr_vec[i]);
					cout << endl << endl << endl << endl;
					pst.print_2d_upright_by_name(expr_vec[i]);
				}
				else
				{
					cout << "Actual result: ";
					pst.parse(expr_vec[i]);
					cout << endl << endl;
				}




				cout << "------- TEST ERFOLGREICH -------" << endl << endl << endl;
			}
			catch (std::exception const& x) {
				std::cerr << "Exception: " << x.what() << endl << endl;
				if (exp_res_vec[i] == "EXCEPTION")
				{
					cout << "------- TEST ERFOLGREICH -------" << endl << endl << endl;
				}
				else
				{
					cout << "-X-X-X- TEST FEHLGESCHLAGEN -X-X-X-" << endl << endl << endl;
				}
			}
		}
	}
	else
	{
		cout << "-X-X-X- TEST FEHLGESCHLAGEN -X-X-X-" << endl << endl << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
}



// TEST for EXCEPTIONS thrown
void test_expression_tree::test_e_t_excp(string const& expr, size_t const test_no, string const& test_txt)
{
	cout << endl << "TESTFALL " << test_no << ": " << test_txt << endl << endl;

	std::cout << "Evaluating expr '" << expr << "' ..." << endl << endl;
	cout << "Expected: EXCEPTION" << endl << endl;

	try {
		xpr::parse_syntax_tree pst;
		cout << "Actual result/exception: ";
		pst.parse(expr);
		cout << endl << endl;
		cout << "-X-X-X- TEST FEHLGESCHLAGEN -X-X-X-" << endl << endl << endl << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	catch (std::exception const& res_excp) {
		cout << res_excp.what() << endl << endl;
		cout << "------- TEST ERFOLGREICH -------" << endl << endl << endl << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;

	}

}





void test_expression_tree::test_undef()
{

}
