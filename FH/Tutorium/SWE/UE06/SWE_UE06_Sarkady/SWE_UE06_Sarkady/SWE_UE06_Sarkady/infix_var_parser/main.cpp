#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include "var_parser.h"
#include "pfc_scanner.h"

using std::cout;
using std::vector;
using std::string;
using std::unordered_map;
using std::setprecision;
using std::fixed;
using std::exception;
using std::cerr;

// test for normal workability
void test_1() {
    cout << "Test 1: Test mit mehreren Rechnungen:\n";

    unordered_map<string, int> const variables{
        { "a", 4 },
        { "b", 7 },
        { "var", 2 }
    };

    vector <string> const expressions{
        "a * 2",
        "b / 3",
        "a + var"
    };

    // sets the number of values displayed after comma
    cout << fixed << setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ VariableParser().parse(xpr, variables) };
            cout << xpr << " = " << value << '\n';
        }
        catch (exception const& x) {
            cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with negative numbers
void test_2() {
    cout << "Test 2: Test mit negativen Zahlen:\n";
    unordered_map<string, int> const variables{
        { "a", -4 },
        { "b", -7 },
        { "var", -2 }
    };

    vector <string> const expressions{
        "a * 2",
        "b / 3",
        "a + var"
    };

    // sets the number of values displayed after comma
    cout << fixed << setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ VariableParser().parse(xpr, variables) };
            cout << xpr << " = " << value << '\n';
        }
        catch (exception const& x) {
            cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test for false calculation
void test_3() {
    cout << "Test 3: Test mit falscher Grammatik:\n";

    unordered_map<string, int> const variables{
      { "a", 4 },
      { "b", 7 },
      { "var", 2 }
    };

    vector <string> const expressions{
        "* a 2",
        "/ b 3"
    };

    // sets the number of values displayed after comma
    cout << fixed << setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ VariableParser().parse(xpr, variables) };
            cout << xpr << " = " << value << '\n';
        }
        catch (exception const& x) {
            cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with empty string
void test_4() {
    cout << "Test 4: Test mit leeren strings:\n";

    unordered_map<string, int> const variables{
       { "a", 0 },
       { "b", 0 },
       { "var", 0 }
    };

    vector <string> const expressions{
        "",
        "",
        ""
    };

    // sets the number of values displayed after comma
    cout << fixed << setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ VariableParser().parse(xpr, variables) };
            cout << xpr << " = " << value << '\n';
        }
        catch (exception const& x) {
            cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

// test with divide by zero
void test_5() {
    cout << "Test 5: Test mit Division durch 0:\n";

    unordered_map<string, int> const variables{
       { "a", 4 },
       { "b", 7 },
       { "var", 0 }
    };

    vector <string> const expressions{
        "a / 0",
        "b / 0",
        "a / var"
    };

    // sets the number of values displayed after comma
    cout << fixed << setprecision(3);

    for (string const& xpr : expressions) {
        try {
            double const value{ VariableParser().parse(xpr, variables) };
            cout << xpr << " = " << value << '\n';
        }
        catch (exception const& x) {
            cerr << "Error: " << x.what() << '\n';
        }
    }
    cout << "\n";
}

int main(int argc, const char* argv[]) {
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
}