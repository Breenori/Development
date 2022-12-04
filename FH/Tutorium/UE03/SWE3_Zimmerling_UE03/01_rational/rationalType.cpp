//
// Created by arzi on 31.10.22.
//

#include "rationalType.h"

rationalType::rationalType() = default;

rationalType::rationalType(rationalType::valueType n, rationalType::valueType d) {
    this->denominator = d;
    this->numerator = n;

    if (!isConsistent()) {
        throw InvalidRationalException();
    }
}

rationalType::rationalType(int n) {
    this->numerator = n;
    this->denominator = 1;
}

rationalType::rationalType(const rationalType &r) {
    numerator = r.numerator;
    denominator = r.denominator;

    if (!isConsistent()) {
        throw InvalidRationalException();
    }
}

bool rationalType::isNegative() const {
    return numerator < 0 || denominator < 0;
}

bool rationalType::isPositive() const {
    return numerator > 0 && denominator > 0;
}

bool rationalType::isZero() const {
    return numerator == 0;
}

void rationalType::add(const rationalType &r) {
    if (denominator == r.denominator) {
        numerator += r.numerator;
    } else {
        numerator = ( numerator * r.denominator ) + ( r.numerator * denominator );
        denominator = denominator * r.denominator;
    }
}

void rationalType::sub(const rationalType &r) {
    if (denominator == r.denominator) {
        numerator -= r.numerator;
    } else {
        numerator = ( numerator * r.denominator ) - ( r.numerator * denominator );
        denominator = denominator * r.denominator;
    }
}

void rationalType::mul(const rationalType &r) {
    numerator *= r.numerator;
    denominator *= r.denominator;
}

void rationalType::div(const rationalType &r) {
    numerator = numerator * r.denominator;
    denominator = denominator * r.numerator;
    if (denominator == 0) {
        throw DivByZeroException();
    }
}

std::string rationalType::toString() const {
    if (denominator == 1) {
        return std::to_string(numerator);
    } else if (numerator % denominator == 0 && numerator != 0) {
        return "1";
    } else {
        if (numerator < 0 || denominator < 0) {
            return "- (" + std::to_string(abs(numerator)) + " / " + std::to_string(abs(denominator)) + ")";
        }
        return std::to_string(numerator) + " / " + std::to_string(denominator);
    }
}

void rationalType::print(std::ostream &os) const {
    os << toString() << std::endl;
}

void rationalType::printResult(rationalType& r, std::ostream& os) {
    r.normalize();
    os << r.toString() << std::endl;
}

rationalType::valueType rationalType::gcd(rationalType::valueType a, rationalType::valueType b) {
    return b == 0 ? a : gcd(b, a%b);
}

void rationalType::normalize() {
    rationalType::valueType greatestCommonDivisor = gcd(numerator, denominator);

    if (greatestCommonDivisor > 1 || greatestCommonDivisor < -1) {
        numerator /= greatestCommonDivisor;
        denominator /= greatestCommonDivisor;
    }
    greatestCommonDivisor = gcd(numerator, denominator);
    if (greatestCommonDivisor > 1 || greatestCommonDivisor < -1) {
        normalize();
    }
}

rationalType rationalType::operator+(const rationalType &r) {
    rationalType tmp = *this;
    tmp.add(r);
    return tmp;
}

rationalType rationalType::operator-(const rationalType &r) {
    rationalType tmp = *this;
    tmp.sub(r);
    return tmp;
}

rationalType rationalType::operator*(const rationalType &r) {
    rationalType tmp = *this;
    tmp.mul(r);
    return tmp;
}

rationalType rationalType::operator/(const rationalType &r) {
    rationalType tmp = *this;
    tmp.div(r);
    return tmp;
}

rationalType &rationalType::operator+=(const rationalType &r) {
    add(r);
    return *this;
}

rationalType &rationalType::operator-=(const rationalType &r) {
    sub(r);
    return *this;
}

rationalType &rationalType::operator*=(const rationalType &r) {
    mul(r);
    return *this;
}

rationalType &rationalType::operator/=(const rationalType &r) {
    div(r);
    return *this;
}

/**
 * Copy-and-swap-idiom
 * @param r
 * @return
 */
rationalType &rationalType::operator=(rationalType r) {
    std::swap(numerator, r.numerator);
    std::swap(denominator, r.denominator);
    return *this;
}

rationalType::valueType rationalType::getNumerator() const {
    return numerator;
}

rationalType::valueType rationalType::getDenominator() const {
    return denominator;
}

void rationalType::setNumerator(rationalType::valueType n) {
    rationalType::numerator = n;
}

void rationalType::setDenominator(rationalType::valueType d) {
    if (d != 0) {
        rationalType::denominator = d;
    } else {
        throw InvalidRationalException();
    }
}

bool rationalType::isConsistent() const {
    return this->denominator != 0;
}

rationalType &rationalType::operator=(const int &lhs) {
    rationalType tmp(lhs);
    std::swap(numerator, tmp.numerator);
    std::swap(denominator, tmp.denominator);
    return *this;
}

rationalType operator+(const int &lhs, const rationalType &rhs) {
    rationalType tmp(lhs);
    tmp.add(rhs);
    return tmp;
}

rationalType operator-(const int &lhs, const rationalType &rhs) {
    rationalType tmp(lhs);
    tmp.sub(rhs);
    return tmp;
}

rationalType operator*(const int &lhs, const rationalType &rhs) {
    rationalType tmp(lhs);
    tmp.mul(rhs);
    return tmp;
}

rationalType operator/(const int &lhs, const rationalType &rhs) {
    rationalType tmp(lhs);
    tmp.div(rhs);
    return tmp;
}

rationalType operator+(const rationalType &lhs, const int &rhs) {
    rationalType tmp(rhs);
    tmp.add(lhs);
    return tmp;
}

rationalType operator-(const rationalType &lhs, const int &rhs) {
    rationalType tmp(rhs);
    tmp.sub(lhs);
    return tmp;
}

rationalType operator*(const rationalType &lhs, const int &rhs) {
    rationalType tmp(rhs);
    tmp.mul(lhs);
    return tmp;
}

rationalType operator/(const rationalType &lhs, const int &rhs) {
    rationalType tmp(rhs);
    tmp.div(lhs);
    return tmp;
}

bool rationalType::operator==(const rationalType &r) const {
    return this->denominator == r.denominator && this->numerator == r.numerator;
}

bool rationalType::operator!=(const rationalType &r) const {
    return this->denominator != r.denominator && this->numerator != r.numerator;
}

bool rationalType::operator>=(const rationalType &r) const {
    double r1 = this->numerator*1.0 / this->denominator;
    double r2 = r.numerator*1.0 / r.denominator;
    if (r1 >= r2) {
        return true;
    } else {
        return false;
    }
}

bool rationalType::operator<=(const rationalType &r) const {
    double r1 = this->numerator*1.0 / this->denominator;
    double r2 = r.numerator*1.0 / r.denominator;
    if (r1 <= r2) {
        return true;
    } else {
        return false;
    }
}

bool rationalType::operator>(const rationalType &r) const {
    double r1 = this->numerator*1.0 / this->denominator;
    double r2 = r.numerator*1.0 / r.denominator;
    if (r1 > r2) {
        return true;
    } else {
        return false;
    }
}

bool rationalType::operator<(const rationalType &r) const {
    double r1 = this->numerator*1.0 / this->denominator;
    double r2 = r.numerator*1.0 / r.denominator;
    if (r1 < r2) {
        return true;
    } else {
        return false;
    }
}

std::ostream &operator<<(std::ostream &lhs, const rationalType &rhs) {
    rationalType a(rhs);
    rhs.printResult(a);
    return lhs;
}

std::istream &operator>>(std::istream &lhs, rationalType &rhs) {
    rhs.scan(lhs);
    return lhs;
}

void rationalType::scan(std::istream& in) {
    try {
        if (in.good()) {
            valueType a, b;
            in >> a >> b;
            rationalType c(a,b);
            this->denominator = c.denominator;
            this->numerator = c.numerator;
        } else {
            std::cout << "Unknown input." << std::endl;
        }
    } catch (InvalidRationalException& e) {
        std::cout << "The entered rational number was not valid." << std::endl;
    }

}

