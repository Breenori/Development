#include <stack>
#include "ArithmeticParserPrefix.h"



int main() {
    std::vector const expressions {
        "+ 1 2"s,               // gives 3, just basic test
        "+ + + 1 2 3 4"s,       // gives 10; 1 + 2 + 3 + 4
        "+ * 2 3 * 4 5"s,       // gives 26; 2 * 3 + 4 * 5
        "* + 2 3 + 4 5"s,       // gives 45; ( 2 + 3 ) * ( 4 + 5 )
        "/ 1 3"s,               // gives a third; 1 / 3
        "/ 5 0"s,               // division by zero
        "+ 2 * 3 4"s,           // gives 14; 2 + 3 * 4
        "- 5 6"s,              // gives -1; 5 - 6
        // negative numbers not possible, leads to SIGSEGV
    };

    for (auto const & xpr : expressions) {
        try {
            std::cout << "\nevaluating expression '" << xpr << "' ...\n";
            auto const value { ArithmeticParserPrefix().parse(xpr) };
            std::cout << "result: " << value << '\n';
        } catch (std::exception const & x) {
            std::cerr << "Error: " << x.what () << '\n';
        }
    }
    return 0;
}
