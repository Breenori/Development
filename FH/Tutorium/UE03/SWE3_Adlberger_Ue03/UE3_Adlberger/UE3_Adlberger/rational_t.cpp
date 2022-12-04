#include "rational_t.h"
#include <stdexcept>
#include"div_by_zero_error.h"
#include <fstream>

#include <vector>

rational_t::rational_t(int _zaehler, int _nenner) :zaehler{ _zaehler }, nenner{ _nenner } {
	if (nenner == 0) {
		std::cout << "not valied";
		
	}
}
rational_t::rational_t(rational_t const& other) {
	nenner = other.nenner;
	zaehler = other.zaehler;
}

bool rational_t::is_consistent()const {
	if (nenner != 0) {
		return true;
	}
	else {
		return false;
	}

}
void rational_t::normalize(int& z, int& n) {
	int low(0);
	int _n=n;
	int _z=n;
	//if the divisor or numerator are negative, 
	//it doesn't work to find the greatest common 
	//divisor because you're searching in the forward
	//loop to the smaller number away from 0
	if (is_negative(n))_n*= (-1);
	if (is_negative(z))_z*= (-1);
	if (z < n)low =  _z;
	else low = _n;
	//search divider
	int teiler = 1;
	for (int i(1); i <= low; ++i) {
		if (n % i == 0 && z % i == 0) {
			teiler = i;
		}
	}
	z = z / teiler;
	n = n / teiler;
}
void rational_t::print(std::ostream& os)const {
	//its 0
	if (zaehler == 0 ) {
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
void rational_t::scan(std::ifstream& in, int& n,int& z)const {
	
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

std::string rational_t::as_string()const {
	return std::to_string(zaehler) + "/" + std::to_string(nenner) ;
}
int rational_t::get_numerator()const {
	return zaehler;
}
int rational_t::get_denominator()const {
	return nenner;
}

bool rational_t:: is_negative(int& const x) {
	if (x < 0) return true;
	else return false;
}
bool rational_t:: is_positive(int& const x) {
	if (x > 0) return true;
	else return false;
}
bool rational_t::is_zero(int& const x) {
	if (x == 0)return true;
	else return false;
}

rational_t& rational_t::operator=(rational_t const& other) {
	if (this == &other) {
		return *this;
	}

	nenner = other.nenner;
	zaehler = other.zaehler;
	return *this;
}

bool rational_t::operator==(rational_t const& other) {
	//rational_t tmp(*this);
	if (nenner == other.nenner && zaehler == other.zaehler)return true;
	else return false;
}
bool rational_t:: operator!=(rational_t const& other) {
	//rational_t tmp(*this);
	if (nenner != other.nenner || zaehler != other.zaehler)return true;
	else return false;
}
bool  rational_t::operator<(rational_t const& other) {
	
	double erg1 = (double)zaehler / (double)nenner;
	double erg2=(double)other.zaehler / (double)other.nenner;
	if (erg1 < erg2)return true;
	else return false;

}
bool  rational_t::operator<=(rational_t const& other) {
	
	double erg1 = (double)zaehler / (double)nenner;
	double erg2 = (double)other.zaehler / (double)other.nenner;
	if (erg1 <= erg2)return true;
	else return false;
}
bool  rational_t::operator>(rational_t const& other) {
	
	double erg1 = (double)zaehler / (double)nenner;
	double erg2 = (double)other.zaehler / (double)other.nenner;
	if (erg1 > erg2)return true;
	else return false;
}
bool  rational_t::operator>=(rational_t const& other) {
	
	double erg1 = (double)zaehler / (double)nenner;
	double erg2 = (double)other.zaehler / (double)other.nenner;
	if (erg1 >= erg2)return true;
	else return false;
}

void rational_t::add(rational_t const& other) {
	zaehler = zaehler * other.nenner + nenner * other.zaehler;
	nenner = nenner * other.nenner;
	optimize();

}
void rational_t::sub(rational_t const& other) {
	zaehler = (zaehler * other.nenner) - (nenner * other.zaehler);
	nenner = nenner * other.nenner;
	optimize();
	//wenn der  zaehler0 ist wird auch der nenner 0
	if (is_zero(zaehler)) {
		nenner = 0;
	}
}
void rational_t::mul(rational_t const& other) {
	zaehler = zaehler * other.zaehler;
	nenner = nenner * other.nenner;
	optimize();
}
void rational_t::div(rational_t const& other) {
	zaehler = zaehler * other.nenner;
	nenner = nenner * other.zaehler;
	optimize();
}

rational_t rational_t::operator+(rational_t const& other) {
	rational_t tmp(*this);
	tmp.add(other);
	if(tmp.is_consistent())return tmp;
}
rational_t rational_t:: operator-(rational_t const& other) {
	rational_t tmp(*this);
	tmp.sub(other);
	return tmp;


}
rational_t rational_t::operator*(rational_t const& other) {
	rational_t tmp(*this);
	tmp.mul(other);
	if (tmp.is_consistent())
		return tmp;
}
rational_t rational_t::operator/(rational_t const& other) {
	rational_t tmp(*this);
	tmp.div(other);
	if (tmp.is_consistent())
		return tmp;
}

rational_t operator+(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp.add(rhs);
	return tmp;
}
rational_t operator-(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp.sub(rhs);
	return tmp;
}
rational_t operator*(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp.mul(rhs);
	return tmp;
}
rational_t operator/(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp.div(rhs);
	return tmp;
}

rational_t& rational_t::operator+=(rational_t const& other) {
	add(other);
	return *this;
}
rational_t& rational_t::operator-=(rational_t const& other) {
	sub(other);
	return *this;
}
rational_t& rational_t::operator*=(rational_t const& other) {
	mul(other);
	return *this;
}
rational_t& rational_t::operator/=(rational_t const& other) {
	div(other);
	return *this;
}

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs) {
	rhs.print(lhs);

	return lhs;
}
std::ifstream& operator>>(std::ifstream& lhs, rational_t const& rhs) {
	int z = rhs.get_denominator();
	int n = rhs.get_numerator();;
	rhs.scan(lhs, n, z);

	return lhs;
}
void print_result(rational_t const& rational)
{	
	std::cout << rational << "\n";
}
void rational_t:: optimize() {
	if (is_negative(zaehler)&& is_negative(nenner)) {
		nenner = nenner * -1;
		zaehler = zaehler * -1;
	}
	normalize(zaehler, nenner);
	if (nenner == -1) {
		zaehler = zaehler * (-1);
		nenner = nenner * -1;
	}
	
}