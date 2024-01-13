/*
* ----- Includes. -----
*/
#include <iostream>
#include <string>
#include <iomanip>
#include "arithmetic_parser_test.h"

/*
* ----- Usings. -----
*/
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::map;

/*
* ----- Functions. -----
*/
void helper_tester(auto const& xpr, string const& exp_output, map<string,double> const& vars) {
    ArithmeticParser ap;
    
    cout << std::fixed << std::setprecision(3);
    cout << "- Input: '" + xpr + "'; " << endl;
    cout << "  Variables: { ";
    for (auto it = vars.begin(); it != vars.end(); ++it) {
        try {
            ap.set_variable(it->first, it->second);
        }
        catch (std::exception const& x) {
            cerr << "Error: " << x.what() << endl;
        }
        cout << it->first << ":" << it->second << " ";
    }    
    cout << "}" << endl;
    cout << "  Output (Expect " + exp_output + "): ";

    try {
        double const value{ ap.parse(xpr) };
        cout << value << endl;
    }
    catch (std::exception const& x) {
        cerr << "Error: " << x.what() << endl;
    }
}

bool test_division_zero() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "((17 * -4) + 8) / x"s,
    };

    map<string, double> vars1; vars1["x"] = 0;
    helper_tester(expressions[0], "Catched Error", vars1);

    cout << endl;
    return 0;
}

bool test_empty() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       ""s,
    };

    map<string, double> vars1; vars1["x"] = 1;
    helper_tester(expressions[0], "Catched Error", vars1);

    cout << endl;
    return 0;
}

bool test_single_numbers() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "x"s,    // Plus
       "-x"s    // Minus
    };

    map<string, double> vars1; vars1["x"] = 6;

    helper_tester(expressions[0], "6", vars1);
    helper_tester(expressions[1], "-6", vars1);

    cout << endl;
    return 0;
}

bool test_multiple_usage() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
        "x+x+x"s
    };

    map<string, double> vars1; vars1["x"] = 4;

    helper_tester(expressions[0], "12", vars1);

    cout << endl;
    return 0;
}

bool test_variables_only() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
        "x+wusel"s,                 // Add
        "wusel*x"s,                 // Mult
        "x-wusel"s,                 // Sub
        "x/wusel"s,                 // Div
        "wusel*x+x"s,               // Mix
        "-wusel+-x"s                // Minus + Minus
    };

    map<string, double> vars1; vars1["x"] = 4; vars1["wusel"] = 5;

    helper_tester(expressions[0], "9", vars1);
    helper_tester(expressions[1], "20", vars1);
    helper_tester(expressions[2], "-1", vars1);
    helper_tester(expressions[3], "0.8", vars1);
    helper_tester(expressions[4], "24", vars1);
    helper_tester(expressions[5], "-9", vars1);

    cout << endl;
    return 0;
}

bool test_parenthesis() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "3*(x+5)"s
    };

    map<string, double> vars1; vars1["x"] = 4;
    helper_tester(expressions[0], "27", vars1);

    cout << endl;
    return 0;
}

bool test_nonsense() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "3+3"s,                  // No Variables
       "3+y"s,                  // variable not set
       "3+hallo welt"s          // variable with multiple words
    };

    map<string, double> vars1; vars1["x"] = 3;
    helper_tester(expressions[0], "6", vars1);
    helper_tester(expressions[1], "Catched Error", vars1);
    vars1["hallo welt"] = 3;
    helper_tester(expressions[1], "Catched variable Error", vars1);

    cout << endl;
    return 0;
}

bool test_custom() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "11 / (-17.3 * y + 3)"s,                 // / - Double in Parenthesis
       "62 / (-seventeen * 2 + 3)"s,            // All Integers; / - Integer in Parenthesis
       "((seventeen * -four) + 8) / -6"s,       // Division Minus. Nested parenthesis
       "1 + twoD + 3 * (minusfive + -4)"s       // * Minus Double
    };

    map<string, double> vars1; vars1["y"] = 22; vars1["seventeen"] = 17; vars1["twoD"] = 2.0; vars1["four"] = 4; vars1["minusfive"] = -5;
    helper_tester(expressions[0], "-0.029", vars1);
    helper_tester(expressions[1], "-2", vars1);
    helper_tester(expressions[2], "10", vars1);
    helper_tester(expressions[3], "-24.0", vars1);

    cout << endl;
    return true;
}