#pragma once
#include <type_traits>

namespace nelms { 

	//neutrales Element für 0
	template <typename T> inline T zero() {
		return T();
	}

	template <>inline int zero() {
		return 0;
	}
	template <> inline double zero() {
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
	template <typename T>
	inline T abs(T const& a) {
		return a;

	}

	template <typename T>
	inline bool divides(T const& a, T const& b){
		return a / b != nelms::zero <T>;

	}

	template <typename T>
	inline bool equals(T const& a, T const& b) {
		return a - b == nelms::zero <T>;

	}

	template <typename T>
	T gcd(T a, T b) {


	}

	template <typename T>
	inline bool is_negative(T const& a) {
		return a < nelms::zero<T>;
	}

	template <typename T>
	inline bool is_zero(T const& a) {
		return a == nelms::zero<T>;

	}

	template <typename T>
	inline T negate(T const& a) {
		return nelms::zero<T> -a;
	}

	template <typename T>
	inline T remainder(T const& a, T const& b) {


	}
}