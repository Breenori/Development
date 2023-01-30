#ifndef rational_t_h
#define rational_t_h
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include"number_t.h"
#include"operations.h"

template<typename T>
concept Numeric = requires (T v) {
	v + v; //T requires operator +
	v - v;
	v* v;
	v / v;
	v += v; 
	v -= v;
	v*= v;
	v /= v;
	v == v;
	v != v;
	v < v;
	v > v;
	v <= v;
	v >= v;
	std::cout << v;
	
};
template<Numeric T=int>
class rational_t {

	T zaehler;
	T nenner;

	friend inline std::ostream& operator<<(std::ostream& lhs, rational_t<T> const& rhs) {
		rhs.print(lhs);
		return lhs;
	}
	friend inline bool operator==(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		//rational_t tmp(*this);
		if (lhs.nenner == rhs.nenner && lhs.zaehler == rhs.zaehler)return true;
		else return false;
	}
	friend inline bool operator!=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		//rational_t tmp(*this);
		if (lhs.nenner != rhs.nenner || lhs.zaehler != rhs.zaehler)return true;
		else return false;
	}
	friend inline bool operator<(rational_t<T> const& lhs, rational_t<T> const& rhs) {

		T erg1 = lhs.zaehler /  lhs.nenner;
		T erg2 =  rhs.zaehler /  rhs.nenner;
		if (erg1 < erg2)return true;
		else return false;

	}
	friend inline bool operator<=(rational_t<T> const& lhs, rational_t<T> const& rhs) {

		T erg1 =  lhs.zaehler / lhs.nenner;
		T erg2 = rhs.zaehler / rhs.nenner;
		if (erg1 <= erg2)return true;
		else return false;
	}
	friend inline bool operator>(rational_t<T> const& lhs, rational_t<T> const& rhs) {

		T erg1 = lhs.zaehler / lhs.nenner;
		T erg2 = rhs.zaehler / rhs.nenner;
		if (erg1 > erg2)return true;
		else return false;
	}
	friend inline bool operator>=(rational_t<T> const& lhs, rational_t<T> const& rhs) {

		T erg1 = lhs.zaehler / lhs.nenner;
		T erg2 = rhs.zaehler / rhs.nenner;
		if (erg1 >= erg2)return true;
		else return false;
	}

	friend inline rational_t<T> operator+(rational_t<T> const& lhs, rational_t<T> const& rhs) {

		rational_t<T> tmp(lhs);
		tmp.add(rhs);
		if (tmp.is_consistent())return tmp;
	}
	friend inline rational_t<T> operator-(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.sub(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator*(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.mul(rhs);
		if (tmp.is_consistent())
			return tmp;
	}
	friend inline rational_t<T> operator/(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.div(rhs);
		if (tmp.is_consistent())
			return tmp;
	}


	friend inline std::ifstream& operator>>(std::ostream& lhs, rational_t<T> const& rhs) {
		T z = rhs.get_denominator();
		T n = rhs.get_numerator();;
		rhs.scan(lhs, n, z);

		return lhs;
	}

	friend inline rational_t<T> operator+=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.add(rhs);
		if (tmp.is_consistent())return tmp;
	}
	friend inline rational_t<T> operator-=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.sub(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator*=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.mul(rhs);
		if (tmp.is_consistent())
			return tmp;
	}
	friend inline rational_t<T> operator/=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.div(rhs);
		if (tmp.is_consistent())
			return tmp;
	}
	friend inline rational_t<T> operator+(int const& lhs, rational_t const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.add(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator-(int const& lhs, rational_t const& rhs){
		rational_t<T> tmp(lhs);
		tmp.sub(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator*(int const& lhs, rational_t const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.mul(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator/(int const& lhs, rational_t const& rhs) {
		rational_t<T> tmp(lhs);
		tmp.div(rhs);
		return tmp;
	}
public:
	void inverse() {
		T tmp = nenner;
		nenner = zaehler;
		zaehler = tmp;
	}
	rational_t(T _zaehler = 0, T _nenner = 1) :zaehler{ _zaehler }, nenner{ _nenner } {
		if (nenner == 0) {
			std::cout << "not valid";
		}
	}
	rational_t(rational_t<T> const& other) {
		nenner = other.nenner;
		zaehler = other.zaehler;
	}
	rational_t() {

	}
	int get_numerator()const {
		return zaehler;
	}
	int get_denominator()const {
		return nenner;
	}
	std::string as_string()const {
		return std::to_string(zaehler) + "/" + std::to_string(nenner);
	}
	bool is_negative(T& const x) {
		if (x < nelms::zero<T>() ) return true;
		else return false;
	}
	bool is_positive(T& const x) {
		if (x > nelms::zero<T>()) return true;
		else return false;
	}
	bool is_zero(T& const x) {
		if (ops::is_zero(x))return true;
		else return false;
	}
	bool is_consistent()const {
		if (nenner != nelms::zero<T>()) {
			return true;
		}
		else {
			return false;
		}

	}
	void optimize() {
		if (is_negative(zaehler) && is_negative(nenner)) {
			nenner = nenner * -1;
			zaehler = zaehler * -1;
		}
		normalize(zaehler, nenner);
		if (nenner == -1) {
			zaehler = zaehler * (-1);
			nenner = nenner * -1;
		}
	}

	void add(rational_t<T> const& other) {
		zaehler = zaehler * other.nenner + nenner * other.zaehler;
		nenner = nenner * other.nenner;
		optimize();

	}
	void sub(rational_t<T> const& other) {
		zaehler = (zaehler * other.nenner) - (nenner * other.zaehler);
		nenner = nenner * other.nenner;
		optimize();
		//wenn der  zaehler0 ist wird auch der nenner 0
		if (is_zero(zaehler)) {
			nenner = 0;
		}
	}
	void mul(rational_t<T> const& other) {
		zaehler = zaehler * other.zaehler;
		nenner = nenner * other.nenner;
		optimize();
	}
	void div(rational_t<T> const& other) {
		zaehler = zaehler * other.nenner;
		nenner = nenner * other.zaehler;
		optimize();
	}
	void print(std::ostream& os)const {
		//its 0
		if (zaehler == 0) {
			os << 0 << "";
		}
		//integer
		else if (nenner == 1) {
			os << zaehler << "";
		}
		else {
			os << zaehler << "/" << nenner << "";
		}
	}
	void scan(std::ifstream& in, T& n, T& z)const {

		std::vector<std::string> input;
		std::string line;
		std::string d;
		int x = 0;
		//file is ok
		if (in.good()) {

			while (std::getline(in, line, '/'))
			{
				input.push_back(line);
			}
			std::getline(in, line);


			if (input.size() != 2) {
				std::cout << "\nincorrect input";
			}
			else {
				bool check(true);
				for (int j(0); j < input.size(); ++j) {
					for (int i(0); i < input[j].size() - 1; ++i) {
						if (!isdigit(input[j][i])) {
							check = false;
						}

					}
				}

				if (check) {

					z = std::stoi(input[0]);
					n = std::stoi(input[1]);


				}
				else {
					std::cout << "\nno digit";
				}
				std::cout << z << "/" << n;
			}
		}//file is not good
		else {
			std::cout << "\nfile is damaged";
		}

	}
private:
	void normalize(T& z, T& n) {
		T low(0);
		T _n = n;
		T _z = z;
		//if the divisor or numerator are negative, 
		//it doesn't work to find the greatest common 
		//divisor because you're searching in the forward
		//loop to the smaller number away from 0
		if (is_negative(n))_n =_n* (-1);
		if (is_negative(z))_z =_n* (-1);
		if (z < n)low = _z;
		else low = _n;
		//search divider
		
		//modulo does not work with datatyp T....it only works with int 
		//it is not possible to find the divider
		/*int teiler = 1;
		for (int i(1); i < low+1; ++i) {
			if (n_int % i == 0 && z_int % i == 0) {
				teiler = i;
			}
		}
		z = z / teiler;
		n = n / teiler;*/
	}
};
template<typename T>
void print_result(rational_t<T> const& rational)
{
	std::cout << rational << "\n";
}
template<typename T>
std::ostream& operator<<(std::ostream& lhs, rational_t<T> const& rhs) {
	rhs.print(lhs);
	return lhs;
}
template<typename T>
std::ifstream& operator>>(std::ifstream& lhs, rational_t<T> const& rhs) {
	T z = rhs.get_denominator();
	T n = rhs.get_numerator();;
	rhs.scan(lhs, n, z);

	return lhs;
}

#endif
