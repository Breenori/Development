#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
* ----- Includes. -----
*/
#include <type_traits>
#include <cmath>

// Nr: 6
namespace nelms { 
	/*
	* Get natural zero.
	* 
	* return T
	*/
	template<typename T>
	inline T zero() { 
		return  T(); 
	}
	template<>
	inline int zero() {
		return 0;
	}

	/*
	* Get natural one.
	*
	* return T
	*/
	template<typename T>
	inline T one() {
		return std::integral_constant<T, 1>::value;
	}
	template<>
	inline int one() {
		return 1;
	}
}

// Nr: 5 & 7
namespace ops {
	/*
	* Return true if negative.
	*
	* return bool
	*/
	template<typename T>
	inline bool is_negative(T const& a) {
		return a < nelms::zero<T>();
	}
	template<>
	inline bool is_negative(int const& a) {
		return a < nelms::zero<int>();
	}

	/*
	* Change sign.
	*
	* return T
	*/
	template<typename T>
	inline T negate(T const& a) {
		return nelms::zero<T>() - a;
	}
	template<>
	inline int negate(int const& a) {
		return nelms::zero<int>() - a;
	}

	/*
	* Absolute amount.
	*
	* return T
	*/
	template<typename T>
	inline T abs(T const& a) {
		return is_negative(a) ? negate(a) : a;
	}
	template<>
	inline int abs(int const& a) {
		return is_negative(a) ? negate(a) : a;
	}

	/*
	* Remainder at division.
	*
	* return T
	*/
	template<typename T>
	inline T remainder(T const& a, T const& b) {
		return (b == nelms::zero<T>() ? a : a % b);
	}
	template<>
	inline int remainder(int const& a, int const& b) {
		return (b == nelms::zero<int>() ? a : a % b); // % only support int.
	}

	/*
	* If a is dividable by b without remainder.
	*
	* return bool
	*/
	template<typename T>
	inline bool divides(T const& a, T const& b) {
		return remainder(a, b) == 0;
	}
	template<>
	inline bool divides(int const& a, int const& b) {
		return remainder(a, b) == 0;
	}

	/*
	* Return true if equal.
	*
	* return bool
	*/
	template<typename T>
	inline bool equals(T const& a, T const& b) {
		return a == b;
	}
	template<>
	inline bool equals(int const& a, int const& b) {
		return a == b;
	}

	/*
	* Return greatest common divider.
	*
	* return T
	*/
	template<typename T>
	inline T gcd(T a, T b) {
		return b == nelms::zero<T>() ? a : gcd(b, a % b);
	}
	template<>
	inline int gcd(int a, int b) {
		return b == nelms::zero<int>() ? a : gcd(b, a % b);
	}

	/*
	* Return neutral zero value.
	*
	* return bool
	*/
	template<typename T>
	inline bool is_zero(T const& a) {
		return a == nelms::zero<T>();
	}
	template<>
	inline bool is_zero(int const& a) {
		return a == nelms::zero<int>();
	}
}

#endif
