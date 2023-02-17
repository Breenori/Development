//       $Id: main.cpp 45068 2021-11-26 17:09:08Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/pfc/trunk/scanner/arithmetic-parser/src/main.cpp $
// $Revision: 45068 $
//     $Date: 2021-11-26 18:09:08 +0100 (Fr., 26 Nov 2021) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: November 6, 2020
// Copyright: (c) 2020 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#include "arithmetic_parser.h"
#include <iomanip>
#include <vector>

// -------------------------------------------------------------------------------------------------

int main() {
	//Buggy,Untest, to be excluded! Thx
	std::vector const expressions{
	   "*22",
	   ":22",
	  ":20",
	  "( (",
	  ")",
	  "+23",
	  "((-32)",
	  "(+23)(-32)",
	  "{",
	  "",
	  "4",
	  "-3",
	  "*",
	};

	std::cout << std::fixed
		<< std::setprecision(3);
	size_t counter{ 0 };
	for (auto const& xpr : expressions) {
		try {
			std::cout << "\nTest" << counter << ": '" << xpr << "' ...\n";

			auto const value{
			   arithmetic_parser().parse(xpr)
			};

			std::cout << "result: " << value << '\n';
		}
		catch (std::exception const& x) {
			std::cerr << "Error: " << x.what() << '\n';
		}
		counter++;
	}
}