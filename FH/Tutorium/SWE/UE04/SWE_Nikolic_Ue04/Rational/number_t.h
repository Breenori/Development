#ifndef number_H
#define number_H

template <typename T>
class number_t {
	T value;

public:

	number_t() {
		value = 1;
	}

	number_t(T const& _value)
	{
		value = _value;
	}

	number_t(number_t const& n) {
		value = n.value;
	}

	std::string as_string() const {
		return std::to_string(value);
	}

	friend inline number_t<T> operator+(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.value += rhs.value;
		return tmp;
	}

	friend inline number_t<T> operator-(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.value -= rhs.value;
		return tmp;
	}

	friend inline number_t<T> operator*(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.value *= rhs.value;
		return tmp;
	}

	friend inline number_t<T> operator/(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.value /= rhs.value;
		return tmp;
	}

	friend inline number_t<T> operator%(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.value = tmp.value % rhs.value;
		return tmp;
	}

	friend inline bool operator==(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value == rhs.value;
	}

	friend inline bool operator<(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value < rhs.value;
	}

	friend inline bool operator>(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value > rhs.value;
	}

	friend inline std::ostream& operator<<(std::ostream& lhs, number_t<T> const& rhs) {
		lhs << rhs.value;
		return lhs;
	}

	friend inline std::istream& operator>>(std::istream& lhs, number_t<T>& rhs) {
		lhs >> rhs.value;
		return lhs;
	}

};

namespace nelms {
	template<>
	inline number_t<int> zero() {
		return number_t(0);
	}

	template<>
	inline number_t<int> one() {
		return number_t(1);
	}
}

#endif // !number_H