#pragma once
#include "rational_extended.h"

namespace nelms {
	template <typename T>
	inline T zero() {
		return T();
	}

	template <typename T>
	inline T one() {
		return std::integral_constant<T, 1>::value;
	}

	template <>
	inline int zero() {
		return 0;
	}

	template <>
	inline int one() {
		return 1;
	}

	template <>
	inline double zero() {
		return 0.0;
	}

	template <>
	inline double one() {
		return 1.0;
	}
}

namespace ops {
	template <typename T>
	inline bool is_negative(T const& a) {
		return a < nelms::zero<T>();
	}

	template <typename T>
	inline T negate(T const& a) {
		return -a;
	}

	template <typename T>
	inline T abs(T const& a) {
		if (is_negative(a)) {
			return negate(a);
		}
		return a;
	}

	template <typename T>
	inline T remainder(T const& a, T const& b) {
		return a % b;
	}

	template <>
	inline double remainder(double const& a, double const& b) {
		return fmod(a, b);
	}

	template <typename T>
	inline bool divides(T const& a, T const& b) {
		return ops::remainder(a, b) == 0;
	}

	template <typename T>
	inline bool equals(T const& a, T const& b) {
		return a == b;
	}

	template <typename T>
	inline T gcd(T a, T b) {
		if (equals(b, nelms::zero<T>())) {
			return a;
		}
		return gcd(b, remainder(a, b));
	}

	template <>
	inline double gcd(double a, double b) {
		return nelms::one<double>();
	}

	template <typename T>
	inline bool is_zero(T const& a) {
		return a == nelms::zero<T>();
	}
}