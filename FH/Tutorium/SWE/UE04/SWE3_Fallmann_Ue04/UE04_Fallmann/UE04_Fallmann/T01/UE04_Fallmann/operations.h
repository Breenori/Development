#pragma once

#include <type_traits>



namespace nelms {

	template<typename T>
	inline T zero() {
		return T();
	}

	template<typename T>
	inline T one() {
		return std::integral_constant<T, 1>::value;
	}

	template<>
	inline int zero() {
		return 0;
	}

	template<>
	inline int one() {
		return 1;
	}

}


namespace ops {

	template<typename T>
	inline T remainder(T const& a, T const& b) {
		return a % b;
	}

	template<>
	inline int remainder(int const& a, int const& b) {
		return a % b;
	}

	template<>
	inline double remainder(double const& a, double const& b) {
		double result = a / b;
		int whole_nr = a / b;

		int r = (result - whole_nr) * b * 1000;
		return r / 1000.0;
	}

	template<>
	inline float remainder(float const& a, float const& b) {
		double result = a / b;
		int whole_nr = a / b;

		int r = (result - whole_nr) * b * 1000;
		return r / 1000.0;
	}

	template <typename T>
	inline T abs(T const& a) {
		return (a >= nelms::zero<T>()) ? a : a * -1;
	}

	template <>
	inline int abs(int const& a) {
		return (a >= nelms::zero<int>()) ? a : a * -1;
	}

	template<typename T>
	inline bool divides(T const& a, T const& b) {
		return (a>=b)?(ops::remainder<T>(a, b) == nelms::zero<T>()):false;
	}

	template<>
	inline bool divides(int const& a, int const& b) {
		return (a>=b)?(ops::remainder<int>(a, b) == nelms::zero<int>()):false;
	}

	template<typename T>
	inline bool equals(T const& a, T const& b) {
		return a == b;
	}

	template<>
	inline bool equals(int const& a, int const& b) {
		return a == b;
	}


	template<typename T>
	inline bool is_negative(T const& a) {
		return a < nelms::zero<T>();
	}

	template<>
	inline bool is_negative(int const& a) {
		return a < 0;
	}

	template<typename T>
	inline bool is_zero(T const& a) {
		return a == nelms::zero<T>();
	}

	template<>
	inline bool is_zero(int const& a) {
		return a == 0;
	}

	template<typename T>
	inline T negate(T const& a) {
		return nelms::zero<T>() - a;
	}

	template<>
	inline int negate(int const& a) {
		return 0 - a;
	}


	template<typename T>
	inline T gcd(T a, T b) {

		if (ops::remainder(a, b) > nelms::zero<T>()) {
			T tmp = remainder<T>(a, b);
			a = b;
			b = tmp;
			gcd(a, b);
		}
		return b;

	}

	template<>
	inline int gcd(int a, int b) {

		if (ops::remainder<int>(a, b) > 0) {
			int tmp = remainder<int>(a, b);
			a = b;
			b = tmp;
			gcd(a, b);
		}
		return b;

	}
}
