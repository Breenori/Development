//
// Created by Hakim Bajim on 10.11.22.
//

#ifndef SWE_BAJIM_UE03_RATIONAL_T_H
#define SWE_BAJIM_UE03_RATIONAL_T_H

#include <iostream>
#include <string>

class rational_t {

    typedef int value_t;

    value_t n; //numerator
    value_t d; //denominator

    // friend functions for reading and printing
    friend std::ostream &operator<<(std::ostream &lhs, const rational_t &r);

    friend std::istream &operator>>(std::istream &lhs, rational_t &r);

public:
    // default constructor
    [[maybe_unused]] rational_t();

    // copy constructor
    [[maybe_unused]] rational_t(const rational_t &src);

    // makes conversion
    [[maybe_unused]] explicit rational_t(value_t numerator = 1, value_t denominator = 1);

    // de-constructor
    [[maybe_unused]] ~rational_t();

    [[maybe_unused]] [[nodiscard]] double normalize() const;

    [[maybe_unused]] [[nodiscard]] std::string as_string() const;

    [[maybe_unused]] [[nodiscard]] value_t get_numerator() const;

    [[maybe_unused]] [[nodiscard]] value_t get_denominator() const;

    [[maybe_unused]] [[nodiscard]] bool is_negative() const;

    [[maybe_unused]] [[nodiscard]] bool is_positive() const;

    [[maybe_unused]] [[nodiscard]] bool is_zero() const;

    [[maybe_unused]] [[nodiscard]] rational_t &operator=(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] rational_t operator+(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] rational_t operator+=(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] rational_t operator-(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] rational_t operator-=(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] rational_t operator*(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] rational_t operator*=(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] rational_t operator/(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] rational_t operator/=(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] bool equals(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] bool unequals(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] bool bigger(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] bool smaller(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] bool equals_bigger(const rational_t &o) const;

    [[maybe_unused]] [[nodiscard]] bool equals_smaller(const rational_t &o) const;

    [[maybe_unused]] std::ostream &print(std::ostream &out = std::cout) const;

    //todo scan
    [[maybe_unused]] std::istream &scan(std::istream &in = std::cin);

private:

    [[maybe_unused]] [[nodiscard]] bool is_consistent(const rational_t &src) const;

    [[maybe_unused]] [[nodiscard]] rational_t add(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] rational_t sub(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] rational_t mul(const rational_t &o);

    [[maybe_unused]] [[nodiscard]] rational_t div(const rational_t &o);

    [[maybe_unused]] void get_to_same_denominator(value_t &n_, value_t &d_);

};

//non-member functions
[[maybe_unused]] [[nodiscard]] rational_t operator+(const int &o, rational_t &r);

[[maybe_unused]] [[nodiscard]] rational_t operator-(const int &o, rational_t &r);

[[maybe_unused]] [[nodiscard]] rational_t operator*(const int &o, rational_t &r);

[[maybe_unused]] [[nodiscard]] rational_t operator/(const int &o, rational_t &r);

[[maybe_unused]] [[nodiscard]] std::ostream &operator<<(std::ostream &lhs, const rational_t &r);

[[maybe_unused]] [[nodiscard]] std::istream &operator>>(std::istream &lhs, rational_t &r);

#endif //SWE_BAJIM_UE03_RATIONAL_T_H
