#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "arithmetic_parser.h"
#include "pfc_scanner.h"

using std::cout;
using std::vector;
using std::string;

// test for normal workability
void test_1() {
    cout << "Test 1: Test mit mehreren Rechnungen:\n";

    vector <string> const expressions{
    "(17 * 22 + 3) / 11",       // 34.273
    "(-17 * 2 + 3) / 62",       // -0.5
    "(17 * 4) + 8 / 6",         // 69.333
    "1 + 2.0 + 3 * (-5 + -4)"   // -24
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with negative numbers
void test_2() {
    cout << "Test 2: Test mit negativen Zahlen:\n";

    vector <string> const expressions{
    "-5 * -3.5 - (-5 + -2.33)",    // gives  24.83
    "(8 * -13) / 22"       // gives  -0.2127
    };

    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test for false calculation
void test_3() {
    cout << "Test 3: Test mit falscher Grammatik:\n";

    vector <string> const expressions{
    "*7 / 12 "
    };
    // this test should give me an exception because the factor is wrong and cannot be parsed correctly

    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with variable
void test_4() {
    cout << "Test 4: Test mit Variablen:\n";

    vector <string> const expressions{
    "(17.3 * 22 + b) / 11",    // Error parsing Term
    "(wow * 2 + 3) / 3",      // Error parsing Expression
    "((17 * -4) + yes) / -6",   // Error parsing Term
    "1 + i + j * (-5 + -4)"     // Error parsing Term
    };

    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with empty strings
void test_5() {
    cout << "Test 5: Test mit leeren strings:\n";
    // Error
    vector <string> const expressions{
    "",     
    "",     
    "",     
    ""      
    };

    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with divide by zero
void test_6() {
    cout << "Test 6: Test mit Division durch 0:\n";

    vector <string> const expressions{
    "3 / 0",     // Error Division by zero
    "5 / 0",     // Error Division by zero
    "0 / 17"     // 0
    };

    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

void test_7() {
    std::cout << "Test 7: Test with wrong paranthesis:\n";
    vector <string> const expressions{
    "1 + 2.0 + 3 * (-5 + -4"   // error, right paranthesis missing
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

void main() {
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();
    test_7();
}