#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <type_traits>
//neutral elements
namespace nelms {
	template<typename T>inline T zero() {
		return T();
	}
	template<>inline int zero() {
		return 0;
	}
	template<>inline double zero() {
		return 0.0;
	}
	template<>inline float zero() {
		return 0.0;
	}
	template<typename T>inline T one() {
		return std::integral_constant<T, 1>::value;
	}
	template<>inline int one() {
		return 1;
	}
	template<>inline double one() {
		return 1.0;
	}
	template<>inline float one() {
		return 1.0;
	}
}
//operations
namespace ops {
	template <typename T>inline T abs(T const& a) {
		return (a >= nelms::zero<T>()) ? a : a * -1;
	}
	template<typename T>inline T remainder(T const& a, T const& b) {
		return a % b;
	}
	template<>inline double remainder(double const& a, double const& b) {
		double tmp = a / b;
		int tmp2 = a / b;
		int result = (tmp - tmp2) * b * 1000;
		return result / 1000.0;
	}
	template<>inline float remainder(float const& a, float const& b) {
		double tmp = a / b;
		int tmp2 = a / b;
		int result = (tmp - tmp2) * b * 1000;
		return result / 1000.0;
	}
	template<typename T>inline bool divides(T const& a, T const& b) {
		return remainder<T>(a, b) == nelms::zero<T>();
	}
	template<typename T>inline bool equals(T const& a, T const& b) {
		return a == b;
	}
	template<typename T>inline T gcd(T a, T b) {
		if (b == nelms::zero<T>()) { return a; }
		return ops::gcd(b, remainder<T>(a,b));
	}
	template<typename T>inline bool is_negative(T const& a) {
		return a < nelms::zero<T>();
	}
	template<typename T>inline bool is_zero(T const& a) {
		return a == nelms::zero<T>();
	}
	template<typename T>inline T negate(T const& a) {
		return nelms::zero<T>() - a;
	}
};

#endif // !OPERATIONS_h
