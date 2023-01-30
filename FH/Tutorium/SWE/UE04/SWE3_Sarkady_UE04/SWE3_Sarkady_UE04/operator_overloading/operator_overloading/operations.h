#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <type_traits>

namespace nelms { // neutral elements for complex construction
	// spezialisierungen für jeden typ (int) traits

	template<typename T> inline T zero() {
		return 0;
	}

	template<> inline int zero() {
		return 0;
	}

	// für jede spezialisierung brauchen wir ein trait mit dem grund template selber
	template<typename T> inline T one() {
		//return std::integral_constant<T, 1>;
		return 1;
	}

	template<> inline int one() {
		return 1;
	}
}

namespace ops {
	template<typename T> inline T abs(T const& a) {
		/*if (ops::is_negative(a)) {
			return a * -1;
		}
		return a;*/
	}

	template<typename T> inline bool divides(T const& a, T const& b) {
		return a % b == nelms::zero<T>();
	}

	template<typename T> inline bool equals(T const& a, T const& b) {
		//return a - nelms::zero<T>() == b - nelms::zero<T>();
		return a - b == nelms::zero<T>();
	}

	template<typename T> inline bool is_negative(T const& a) {
		// was immer T ist, es muss eine zero funktion geben
		return a < nelms::zero<T>();
	}

	template<typename T> inline bool is_zero(T const& a) {
		return a == nelms::zero<T>();
	}

	template<typename T> inline T negate(T const& a) {
		return nelms::zero<T>() - a;
	}

	template<typename T> inline T remainder(T const& a, T const& b) {
		return a % b;
	}

	template<typename T> inline T gcd(T n, T d) {
		if (d == nelms::zero<T>()) {
			return n;
		}
		return ops::gcd(d, ops::remainder(n, d));
	}
}
#endif
