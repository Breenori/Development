//
//  main.cpp
//  arithmetic_parser
//
//  Created by Andreas Schuler on 07.12.19.
//  Copyright � 2019 Andreas Schuler. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include "arithmetic_parser.h"

int main(int argc, const char* argv[]) {
    std::vector <std::string> const expressions{
        "11 / (-17.3 * 22 + 3)",    // gives  -0.0291314
        "(62 / (-17 * 2 + 3)) * variable1 + 5",       // gives  1
        "((17 * -4) + 8) / zero",     // gives  10
        "1 + 2.0 + 3 * (-5 + -4)",   // gives -24
        "1 / 0"
    };

    ArithmeticParser ap;
    ap.set_variable("variable1", 2);
    ap.set_variable("zero", 0);
	

    // sets the number of values displayed after comma
    std::cout << std::fixed << std::setprecision(3);

    for (std::string const& xpr : expressions) {
        try {
            double const value{ ap.parse(xpr) };
            std::cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
}