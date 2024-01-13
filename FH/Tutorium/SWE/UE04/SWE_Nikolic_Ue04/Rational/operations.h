#ifndef operations_h
#define operations_h

#include<type_traits>

namespace nelms { // neutral elements
	template <typename T>
	inline T zero() {
		return T();
	}

	template <typename T>
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
	template <typename T>
	inline bool is_negative(T const& a) {
		return a < nelms::zero<T>();
	}

	template<typename T>
	inline bool equals(T const& a, T const& b) {
		return a == b;
	}

	template<typename T>
	inline bool is_zero(T const& a) {
		return equals(a, nelms::zero<T>());
	}

	template<typename T>
	inline T negate(T const& a) {
		return is_negative(a) ? a : nelms::zero<T>() - a;
	}

	template<typename T>
	inline T remainder(T const& a, T const& b) {
		return a % b;
	}

	template<typename T>
	inline T abs(T const& a) {
		return (ops::is_negative(a) ? nelms::zero<T>() - a : a);
	}



	template<typename T>
	inline bool divides(T const& a, T const& b) {
		return equals(remainder(a,b), nelms::zero<T>());
	}

	

	template<typename T>
	inline T gcd(T const& a, T const&  b) {
		T denom(abs(abs(a) < abs(b) ? a : b));
		while (denom>0)
		{
			if (divides(a,denom) && divides(b,denom)) return denom;

			denom = denom - nelms::one<T>();
		}
		return 1;
	}



}

#endif // !operations_h

