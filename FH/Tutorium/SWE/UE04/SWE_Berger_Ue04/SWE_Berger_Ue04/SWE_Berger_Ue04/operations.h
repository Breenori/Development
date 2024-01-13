#ifndef operations_h
#define operations_h

#include <type_traits>
#include "rational_type.h"
#include "div_by_zero_error.h"
#include <iostream>


namespace nelms {

	template <typename T> inline T one() {
		return std::integral_constant<T, 1>::value;
	}
	template<> inline int one() {
		return 1;
	}
	template<> inline double one() {
		return 1.0;
	}
	template<typename T> inline T zero() {
		return T();
	}
	template<> inline int zero() {
		return 0;
	}
	template<> inline double zero() {
		return 0.0;
	}
}

namespace ops {
	template<typename T> inline T abs(T const& a) {
		return a < nelms::zero<T>() ? a * (-1) : a;
	}
	template<typename T> inline bool divides(T const& a, T const& b) {
		return a % b == 0 ? true : false;
	}
	template<typename T> inline bool equals(T const& a, T const& b) {
		return a == b;
	}
	template<typename T> inline T gcd(T a, T b) {
		if (a >= b) {
			std::swap(a, b);
		}

		if (a == nelms::zero<T>()) {
			try {
				throw divide_by_zero_error();
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}
		}
		else {
			T rest = b % a;
			if (rest == nelms::zero<T>()) {
				return a;
			}
			while (rest != 0) {
				rest = b % a;
				b = a;
				a = rest;
			}
			return b;
		}
		return nelms::one<T>();
	}

	template<typename T> inline T lcm(T a, T b, T const gcd) {
		return a * b / gcd;
	}


	template<typename T> inline bool is_negative(T const& a) {
		return a < nelms::zero<T>();
	}
	template<typename T> inline bool is_zero(T const& a) {
		return a == nelms::zero<T>();
	}
	template<typename T> inline T negate(T const& a) {
		return nelms::zero<T>();
	}
	template<typename T> inline T remainder(T const& a, T const& b) {
	
		return a % b;
	}
}




#endif
