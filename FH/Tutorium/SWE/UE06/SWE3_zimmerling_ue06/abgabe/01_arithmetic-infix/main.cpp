#include <iostream>
#include <iomanip>
#include "vector"
#include "arithmetic_parser.h"

int main() {
    std::vector const expressions {
//            "11 / (-17.3 * 22 + 3)"s,    // gives  -0.0291314
//            "62 / (-17 * 2 + 3)"s,       // gives  -2
//            "((17 * -4) + 8) / -6"s,     // gives  10
//            "1 + 2.0 + 3 * (-5 + -4)"s,  // gives -24
            // --------------------------------------
            "7 / 0"s,                    // division by zero
            "- 4 + 4"s,                  // start expression with negative-sign
            "( ( 5 / 2 )"s,              // invalid expression (missing closing parenthesis
            "( 1 + 2 + 3 ) * 2 ) - 8"s,  // -8 is cut off due to closing p. without opening p.
            "( ( (4 + 3 ) ) )"s,         // lots of useless parenthesis
            "3 * - 2"s,                  // leading minus as negative number
            "4 + +"s,                    // "increment" not valid by grammar rules
            "1 4"s,                      // missing factor leads to cutting the trailing end
            "1 + 2 * 3 - 2"s,            // gives 5, priority of factors set by grammar
            "10 + 6 - ( )"s,             // invalid due to empty parenthesis
            "75 a - 13"s,                // illegal character is ignored!
            "45 * a +2"s,                // illegal use of variable
    };

    std::cout << std::fixed << std::setprecision (3);

    for (auto const & xpr : expressions) {
        try {
            std::cout << "\nevaluating expression '" << xpr << "' ...\n";
            auto const value {ArithmeticParserInfix().parse(xpr) };
            std::cout << "result: " << value << '\n';
        } catch (std::exception const & x) {
            std::cerr << "Error: " << x.what () << '\n';
        }
    }
    return 0;
}
