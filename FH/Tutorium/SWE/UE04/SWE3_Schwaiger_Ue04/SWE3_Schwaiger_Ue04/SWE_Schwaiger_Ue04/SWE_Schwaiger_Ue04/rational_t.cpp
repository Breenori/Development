#include "rational_t.h"
#include <type_traits>
#include <stdexcept>

//------------------------------------------------------

//----------------------

template <numeric T>
rational_t<T>::rational_t(rational_t<T> const& other) {
	num = other.num;
	den = other.den;

}
template <numeric T>
rational_t<T>::~rational_t() {

}
template <numeric T>
void rational_t<T>::add(rational_t<T> const& other) {

	num = num * other.den + other.num * den;
	den = den * other.den;
	noramlize();
}

template <numeric T>
void rational_t<T>::sub(rational_t<T> const& other) {
	num = num * other.den - other.num * den
	den = den - other.den;
	noramlize();
}
template <numeric T>
void rational_t<T>::mul(rational_t<T> const& other) {
	T tmp_num = num;
	T tmp_den = den;
	num = (tmp_num * other.num);
	den = (tmp_den * other.den);
	noramlize();
}
template <numeric T>
void rational_t<T>::div(rational_t<T> const& other) {
	T tmp_num = num;
	T tmp_den = den;

	T denom = (other.num * other.num) + (other.den * other.den);
	if (denom == 0) {
		throw div_by_zero();
	}
	num = tmp_num * other.den;
	den = tmp_den * other.num;
	noramlize();
}
template <numeric T>
bool rational_t<T>::compare(rational_t<T> const& other) {
	if (num == other.num && den == other.den) {
		cout << "Are the same!\n";
		return true;
	}
	else {
		cout << "Are not the same\n";
	}
	return false;
}

template <numeric T>
bool rational_t<T>::not_compare(rational_t<T> const& other) {
	if (!!(num == other.num && den == other.den)) {
		cout << "Are not the same !\n";
		return true;
	}
	else {
		cout << "Are the same!\n";
		return false;
	}
}
template <numeric T>
bool rational_t<T>::smaller_than(rational_t<T> const& other) {
	if (num <= other.num) {
		cout << "A is smaler than b\n";
		return true;
	}
	if (num == other.num && den <= other.den) {
		cout << " A is bigger than b\n";
		return true;
	}
	else {
		cout << "A is smaler than b\n";
		return false;
	}
}
template <numeric T>
bool rational_t<T>::greater_than(rational_t<T> const& other) {
	if (num >= other.num) {
		cout << "A is bigger than b\n";
		return true;
	}
	if (num == other.num && den >= other.den) {
		cout << "A is bigger than b\n";
		return true;
	}
	else {
		cout << "A is smaller than b\n";
		return false;
	}
}
template <numeric T>
bool rational_t<T>::smaller(rational_t<T> const& other) {
	if (num < other.num) {
		cout << "A is smaller than b\n";
		return true;
	}
	if (num == other.num && den < other.den) {
		cout << "A is smaller than b\n";
		return true;
	}
	else {
		cout << "A is bigger than b\n";
		return false;
	}

}
template <numeric T>
bool rational_t<T>::greater(rational_t<T> const& other) {
	if (num > other.num) {
		cout << "A is bigger than b\n";
		return true;
	}
	if (num == other.num && den > other.den) {
		cout << "A is bigger than b\n";
		return true;
	}
	else {
		cout << "A is smaler than b\n";
		return false;
	}
}


//OTHER METHODS
template <numeric T>
string rational_t<T>::as_string() const {
	return std::to_string(num) + " / " + std::to_string(den);
}
template <numeric T>
//getter
T rational_t<T>::get_numerator() {
	return num;
}
template <numeric T>
T rational_t<T>::get_denominator() {
	return den;
}
template <numeric T>
void rational_t<T>::is_consistent() {
	if (den = 0) {
		throw unvalid_input();
	};
}

template <numeric T>
void rational_t<T>::noramlize() {
	int a;
	if (abs(num) > abs(den)) {
		a = abs(num + 1);
	}
	else {
		a = abs(den) + 1;
	}
	do { a--; } while ((num % a != 0) || (den % a != 0));
	num = num / a;
	den = den / a;
}


template <numeric T>
void rational_t<T>::is_negative() {
	if (num < 0 || den < 0) {
		cout << "This number is negative\n";
	}
}
template <numeric T>
void rational_t<T>::is_positive() {
	if (num > 0 && den > 0) {
		cout << "This number is positive\n";
	}
}
template <numeric T>
void rational_t<T>::is_zero() {
	if (num == 0 || den == 0) {
		cout << " THis number is zero \n";
	}
}


template <numeric T>
void rational_t<T>::print(std::ostream& out) const {
	out << num << "/" << den;

}
template <numeric T>
void rational_t<T>::scan(std::istream& in) {
	int in_num;
	int in_den;
	cout << "Choose a number for the numerator: \n";
	in >> in_num;
	cout << "Choose a number for the denumerator: \n";
	in >> in_den;
	if (in_den == 0) {
		throw unvalid_input();
	}
	num = in_num;
	den = in_den;

}

template <numeric T>
rational_t<T> rational_t<T>::inverse()const {
	rational_t<T> temp(this->den, this->num);
}





//std::ostream& operator<< (std::ostream& out, rational_t const& other) {
//	other.print(out);
//	return out;
//}
//
//std::istream& operator>>(std::istream& in, rational_t const& other){
//	
//	return in;
//
//}





