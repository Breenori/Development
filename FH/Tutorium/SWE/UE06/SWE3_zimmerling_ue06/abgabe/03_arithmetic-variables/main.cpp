#include <iostream>
#include <iomanip>
#include "vector"
#include "arithmeticVariableParser.h"

int main() {

    ArithmeticVariableParser().setVariable("a", -1);
    ArithmeticVariableParser().setVariable("b", 3);
    ArithmeticVariableParser().setVariable("hugeValue", 100);
    ArithmeticVariableParser().setVariable("x", 42);
    ArithmeticVariableParser().setVariable("y", 5);
    ArithmeticVariableParser().setVariable("ZERO", 0);
    ArithmeticVariableParser().setVariable("ONE", 1);

    std::vector const expressions {
//            "7 / 0"s,                    // division by zero
//            "- 4 + 4"s,                  // start expression with negative-sign
//            "( ( 5 / 2 )"s,              // invalid expression (missing closing parenthesis
//            "( 1 + 2 + 3 ) * 2 ) - 8"s,  // -8 is cut off due to closing p. without opening p.
//            "( ( (4 + 3 ) ) )"s,         // lots of useless parenthesis
//            "3 * - 2"s,                  // leading minus as negative number
//            "4 + +"s,                    // "increment" not valid by grammar rules
//            "1 4"s,                      // missing factor leads to cutting the trailing end
//            "1 + 2 * 3 - 2"s,            // gives 5, priority of factors set by grammar
//            "10 + 6 - ( )"s,             // invalid due to empty parenthesis
            "a"s,                          // gives the value of a which is -1
            "hugeValue + 31 / 2"s,         // gives 115.5: 100 + 31 / 2
            "2 * a - 1"s,                  // gives -3: 2 * -1 - 1
            "3 + -b + 2"s,                 // gives 2: 3 + (-3) + 2
            "5 * z"s,                      // error as z does not exist
            "10  / ZERO"s,                 // division by zero - invalid
            "a * b + hugeValue - ONE"s,    // gives 96: -1 * 3 + 100 - 1
    };

    std::cout << std::fixed << std::setprecision (3);

    for (auto const & xpr : expressions) {
        try {
            std::cout << "\nevaluating expression '" << xpr << "' ...\n";
            auto const value {ArithmeticVariableParser().parse(xpr) };
            std::cout << "result: " << value << '\n';
        } catch (std::exception const & x) {
            std::cerr << "Error: " << x.what () << '\n';
        }
    }
    return 0;
}
