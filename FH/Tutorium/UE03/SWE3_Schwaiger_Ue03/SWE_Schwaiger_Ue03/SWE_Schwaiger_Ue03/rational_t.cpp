#include "rational_t.h"

rational_t::rational_t(int _num , int _den) : num{ _num }, den{ _den } {

}
rational_t::rational_t(rational_t const& other) {
	num = other.num;
	den = other.den;

}
rational_t::~rational_t() {


}

void rational_t::add(rational_t const& other) {
	num = num + other.num;
	den = den + other.num;
	noramlize();
}
void rational_t::sub(rational_t const& other) {
	num = num - other.num;
	den = den - other.den;
	noramlize();
}
void rational_t::mul(rational_t const& other) {
	int tmp_num = num;
	int tmp_den = den;
	num = (tmp_num * other.num);
	den = (tmp_den * other.den);
	noramlize();
}
void rational_t::div(rational_t const& other) {
	int tmp_num = num;
	int tmp_den = den;
	
	int denom = (other.num * other.num) + (other.den * other.den);
	if (denom == 0) {
		throw div_by_zero();
	}
	num = tmp_num * other.num;
	den = tmp_den * other.den;
	noramlize();
}

bool rational_t::compare(rational_t const& other) {
	if (num == other.num && den == other.den) {
		cout << "Are the same!\n";
		return true;
	}
	else {
		cout << "Are not the same\n";
	}
	return false;
}
bool rational_t::not_compare(rational_t const& other) {
	if (!!(num == other.num && den == other.den)) {
		cout << "Are not the same !\n";
		return true;
	}
	else {
		cout << "Are the same!\n";
		return false;
	}
}
bool rational_t::smaller_than(rational_t const& other) {
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
bool rational_t::greater_than(rational_t const& other) {
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
bool rational_t::smaller(rational_t const& other) {
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
bool rational_t::greater(rational_t const& other) {
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


//OPERATOR OVERLOADING

rational_t rational_t::operator+(rational_t const& other) {
	rational_t temp(*this);
	temp.add(other);
	return temp;
}
rational_t rational_t::operator-(rational_t const& other) {
	rational_t temp(*this);
	temp.sub(other);
	return temp;
}
rational_t rational_t::operator*(rational_t const& other) {
	rational_t temp(*this);
	temp.mul(other);
	return temp;
}
rational_t rational_t::operator/(rational_t const& other) {
	rational_t temp(*this);
	temp.div(other);
	return temp;
}

//assignment operator
rational_t& rational_t::operator=(rational_t const& other) {
	if (this == &other) {
		return *this;
	}
	num = other.num;
	den = other.den;
	return *this;
}

rational_t rational_t::operator+=(rational_t const& other) {
	add(other);
	return *this;

}
rational_t rational_t::operator-=(rational_t const& other) {
	sub(other);
	return *this;

}
rational_t rational_t::operator*=(rational_t const& other) {
	mul(other);
	return *this;

}
rational_t rational_t::operator/=(rational_t const& other) {
	div(other);
	return *this;
}


rational_t rational_t::operator==(rational_t const& other) {
	compare(other);
	return *this;
}
rational_t rational_t::operator!=(rational_t const& other) {
	not_compare(other);
	return *this;

}
rational_t rational_t::operator<=(rational_t const& other) {
	smaller_than(other);
	return *this;

}
rational_t rational_t::operator>=(rational_t const& other) {
	greater_than(other);
	return *this;

}
rational_t rational_t::operator<(rational_t const& other) {
	smaller(other);
	return *this;

}
rational_t rational_t::operator>(rational_t const& other) {
	greater(other);
	return *this;

}




//OTHER METHODS

string rational_t::as_string() const {
	return std::to_string(num) + " / " + std::to_string(den);
}

//getter
int rational_t::get_numerator() {
	return num;
}
int rational_t::get_denominator() {
	return den;
}

void rational_t::is_consistent() {
	if (den = 0) {
		throw unvalid_input();
	};
}

void rational_t::noramlize() {
	int a;
	if (abs(num) > abs(den)) {
		a = abs(num + 1);
	}
	else {
		a = abs(den) + 1;
	}
	do { a--; }
	while ((num % a != 0) || (den % a != 0)); 
	num = num / a;
	den = den / a;
}



void rational_t::is_negative() {
	if (num < 0 || den < 0) {
		cout << "This number is negative\n";
	}
}
void rational_t::is_positive() {
	if (num > 0 && den > 0) {
		cout << "This number is positive\n";
	}
}
void rational_t::is_zero() {
	if (num == 0 || den == 0) {
		cout << " THis number is zero \n";
	}
}



void rational_t::print(std::ostream& out ) const {
	out << num << "/" << den;

}

void rational_t::scan(std::istream& in) {
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





