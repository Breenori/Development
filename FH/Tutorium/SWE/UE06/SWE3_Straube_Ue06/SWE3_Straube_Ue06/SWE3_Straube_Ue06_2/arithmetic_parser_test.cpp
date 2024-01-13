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

/*
* ----- Functions. -----
*/
void helper_tester(auto const& xpr, std::string const& exp_output) {
    cout << std::fixed << std::setprecision(3);
    cout << "- Input: '" + xpr + "'; Output (Expect " + exp_output + "): ";

    try {
        double const value{ ArithmeticParser().parse(xpr) };
        cout << value << endl;
    }
    catch (std::exception const& x) {
        cerr << "Error: " << x.what() << endl;
    }
}

bool test_division_zero() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "/ + * 17 - 0 4 8 0"s,
    };

    helper_tester(expressions[0], "Catched Error");

    cout << endl;
    return 0;
}

bool test_empty() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       ""s,
    };

    helper_tester(expressions[0], "Catched Error");

    cout << endl;
    return 0;
}

bool test_single_numbers() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "6"s,    // Plus
       "-2"s    // Minus --> 0 - 2!
    };

    helper_tester(expressions[0], "6");
    helper_tester(expressions[1], "-2");

    cout << endl;
    return 0;
}

bool test_simple_operations() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
        "+ 4 4"s,               // Add
        "* 5 3"s,               // Mult
        "- 4 12"s,              // Sub
        "/ 12 3"s,              // Div
        "+ * 5 3 4"s,           // Mix
        "+ - 0 4 - 0 4"s        // Minus + Minus
    };

    helper_tester(expressions[0], "8");
    helper_tester(expressions[1], "15");
    helper_tester(expressions[2], "-8");
    helper_tester(expressions[3], "4");
    helper_tester(expressions[4], "19");
    helper_tester(expressions[5], "-8");

    cout << endl;
    return 0;
}

bool test_nonsense() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "+ 3 c"s,        // Letters
       "* + * 3 3"s     // Mult Op
    };

    helper_tester(expressions[0], "Catched Error");
    helper_tester(expressions[1], "Catched Error");

    cout << endl;
    return 0;
}

bool test_custom() {
    cout << "--- " << __func__ << ":" << endl;

    std::vector const expressions{
       "/ 11 + * - 0 17.3 22 3"s,       // / - Double in Parenthesis
       "/ 62 + * - 0 17 2 3"s,          // All Integers; / - Integer in Parenthesis
       "/ + * 17 - 0 4 8 -0 6"s,        // Division Minus. Nested parenthesis
       "+ 1 + 2.0 * 3 + - 0 5 - 0 4"s   // * Minus Double
    };

    helper_tester(expressions[0], "-0.029");
    helper_tester(expressions[1], "-2");
    helper_tester(expressions[2], "10");
    helper_tester(expressions[3], "-24.0");

    cout << endl;
    return true;
}