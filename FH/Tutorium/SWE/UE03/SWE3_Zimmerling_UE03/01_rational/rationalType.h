//
// Created by arzi on 31.10.22.
//

#ifndef INC_01_RATIONAL_RATIONALTYPE_H
#define INC_01_RATIONAL_RATIONALTYPE_H

#include "string"
#include "iostream"
#include "exception"
#include "InvalidRationalException.h"
#include "DivByZeroException.h"

class rationalType {
    using valueType = int;

    friend std::ostream& operator<<(std::ostream& lhs, rationalType const& rhs);
    friend std::istream& operator>>(std::istream& lhs, rationalType const& rhs);

public:
    explicit rationalType();
    explicit rationalType(valueType, valueType);
    explicit rationalType (int n);
    rationalType(rationalType const& r);

    static void printResult(rationalType& r, std::ostream& os = std::cout);

    bool isNegative() const;
    bool isPositive() const;
    bool isZero() const;

    void add(rationalType const& r);
    void sub(rationalType const& r);
    void mul(rationalType const& r);
    void div(rationalType const& r);

    rationalType operator+(rationalType const& r);
    rationalType operator-(rationalType const& r);
    rationalType operator*(rationalType const& r);
    rationalType operator/(rationalType const& r);

    rationalType& operator+=(rationalType const& r);
    rationalType& operator-=(rationalType const& r);
    rationalType& operator*=(rationalType const& r);
    rationalType& operator/=(rationalType const& r);

    rationalType& operator=(rationalType r);
    rationalType& operator=(int const& lhs);

    bool operator==(rationalType const& r) const;
    bool operator!=(rationalType const& r) const;
    bool operator>=(rationalType const& r) const;
    bool operator<=(rationalType const& r) const;
    bool operator>(rationalType const& r) const;
    bool operator<(rationalType const& r) const;

    valueType getNumerator() const;
    valueType getDenominator() const;
    void setNumerator(valueType n);
    void setDenominator(valueType d);

    void scan(std::istream& in = std::cin);

private:
    valueType numerator{}; // zaehler
    valueType denominator{}; // nenner
    void print(std::ostream& os = std::cout) const;
    static rationalType::valueType gcd(rationalType::valueType a, rationalType::valueType b);
    bool isConsistent() const;
    void normalize();
    std::string toString() const;

};

// non-member methods
rationalType operator+(int const& lhs, rationalType const& rhs);
rationalType operator+(rationalType const& lhs, int const& rhs);
rationalType operator-(int const& lhs, rationalType const& rhs);
rationalType operator-(rationalType const& lhs, int const& rhs);
rationalType operator*(int const& lhs, rationalType const& rhs);
rationalType operator*(rationalType const& lhs, int const& rhs);
rationalType operator/(int const& lhs, rationalType const& rhs);
rationalType operator/(rationalType const& lhs, int const& rhs);

std::ostream& operator<<(std::ostream& lhs, rationalType const& rhs);
std::istream& operator>>(std::istream& lhs, rationalType&  rhs);



#endif //INC_01_RATIONAL_RATIONALTYPE_H
