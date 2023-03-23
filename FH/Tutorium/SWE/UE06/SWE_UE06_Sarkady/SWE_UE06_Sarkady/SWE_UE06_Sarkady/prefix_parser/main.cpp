#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "prefix_parser.h"
#include "pfc_scanner.h"


using std::string;
using std::cout;
using std::vector;



// test for normal workability
void test_1() {
    cout << "Test 1: Test mit normalen Rechnungen:\n";

    vector <string> const expressions{
    "+ 2 3",            // gives  5
    "/ 6 3",            // gives  2
    "* 5 2",            // gives  10
    "- 2 7",            // gives -5
    "* 7 + 8 / 4 2.2",    // gives 68.727
    "/ * 7 + 8 4 2"     // gives 42
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ PrefixParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test for false calculation
void test_2() {
    cout << "Test 2: Test mit falscher Grammatik:\n";

    vector <string> const expressions{
    "2 + 3",            // gives  Error parsing Factor
    "6 / 3",
    "7 * 8 + (4 / 2)"
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ PrefixParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with variables
void test_3() {
    cout << "Test 3: Test mit Variablen:\n";

    vector <string> const expressions{
    "+ wow 3",              // gives nothing
    "/ 6 b",                // gives nothing
    "* yey + i / 4 2"       // gives nothing
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ PrefixParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with parentheses
void test_4() {
    cout << "Test 4: Test mit Klammern:\n";

    vector <string> const expressions{
    "* 7 + 8 (/ 4 2)"    // gives 70
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ PrefixParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with division by zero
void test_5() {
    cout << "Test 5: Test mit Division durch 0:\n";

    vector <string> const expressions{
    "/ 6 0",           // gives error division with 0
    "* 7 + 8 / 4 0"    // gives error division with 0
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ PrefixParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with empty string
void test_6() {
    cout << "Test 6: Test mit leerem String:\n";

    vector <string> const expressions{
    "",           // gives  5
    ""            // gives  2
    };

    // sets the number of values displayed after comma
    cout << std::fixed << std::setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ PrefixParser().parse(xpr) };
            cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}


int main(int argc, const char* argv[]) {
	//test_1();
	test_2();
	//test_3();
	//test_4();
	//test_5();
	//test_6();
}