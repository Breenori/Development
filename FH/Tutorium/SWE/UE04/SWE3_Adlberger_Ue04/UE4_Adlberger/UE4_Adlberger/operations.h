#ifndef operation_h
#define operation_h

#include<type_traits>

namespace nelms { //neutral elements for rational_t construction
	template<typename T> inline T zero() {
		return T();
	}
	template<> inline int zero() {
		return 0;
	}
	template<> inline double zero() {
		return 0.0;
	}

	template<typename T> inline T one() {
		return std::integral_constant<T, 1>::value;
	}
	template<> inline int one() {
		return 1;
	}
	template<> inline double one() {
		return 1.0;
	}
}

namespace ops {

	template<typename T>
	inline bool is_negative(T const& a) {
		return a < nelms::zero<T>();  // vergleicht mit nullelement aus neutralem Element
	}
	template<typename T>
	inline bool is_zero(T const& a) {
		return a == nelms::zero<T>();
	}
	template<typename T>
	inline T negate(T const& a) {
		return nelms::zero<T> -a;  //bekommen das negative udn wenn negativ dann positiv
	}
	template<typename T>
	inline T abs(T const& a) {
		if (a < 0)return a * (-1);
		else return a;
	}
	template<typename T>
	inline bool divides(T const& a, T const& b) {
		if (a % b == 0) {
			return true;
		}
		else return false;
	}
	template<typename T>
	inline bool equals(T const& a, T const& b) {
		if (a == b)return true;
		else return false;
	}
	template<typename T>
	inline T gcd(T a, T b) {

		while (a != b) {
			if (a > b)
				a -= b;
			else
				b -= a;
		}
		return a;
	}
	template<typename T>
	inline T remainder(T const& a, T const& b) {
		return a / b;
	}
}

#endif // !operation_h
