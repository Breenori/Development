//
// Created by Hakim Bajim on 10.11.22.
//

#include <stdexcept>

#include "rational_t.h"
#include "div_by_zero.h"

//member functions
//constructors
[[maybe_unused]] rational_t::rational_t() {
    this->n = 0;
    this->d = 1;
}

[[maybe_unused]] rational_t::rational_t(const rational_t &src) {
    if (is_consistent(src)) {
        this->n = src.n;
        this->d = src.d;
    } else {
        throw div_by_zero();
    }
}

[[maybe_unused]] rational_t::rational_t(rational_t::value_t numerator, rational_t::value_t denominator) {
    if (denominator == 0) {
        throw div_by_zero();
    } else {
        this->n = numerator;
        this->d = denominator;
    }
}

[[maybe_unused]]rational_t::~rational_t() = default;

//other functions
[[maybe_unused]] [[nodiscard]] double rational_t::normalize() const {
    if (this->d != 0) {
        return (double)this->n / (double)this->d;
    } else {
        throw div_by_zero();
    }
}

[[maybe_unused]] [[nodiscard]] std::ostream &rational_t::print(std::ostream &out) const {
    out << "<" << this->n << "/" << this->d << ">";
    return out;
}

[[maybe_unused]] [[nodiscard]] std::istream &rational_t::scan(std::istream &in) {
    return in;
}

[[maybe_unused]] [[nodiscard]] std::string rational_t::as_string() const {
    if(!is_consistent(*this)) {
        throw div_by_zero();
    }
    std::string tmp("<" + std::to_string(this->n) + "/" + std::to_string(this->d) + ">");
    return tmp;
}

[[maybe_unused]] [[nodiscard]] rational_t::value_t rational_t::get_numerator() const {
    if(!is_consistent(*this)) {
        throw div_by_zero();
    }
    return this->n;
}

[[maybe_unused]] [[nodiscard]] rational_t::value_t rational_t::get_denominator() const {
    if(!is_consistent(*this)) {
        throw div_by_zero();
    }
    return this->d;
}

[[maybe_unused]] [[nodiscard]] bool rational_t::is_negative() const {
    // case that both n and d are negative, means its positive
    if(!is_consistent(*this)) {
        throw div_by_zero();
    }
    if (this->n < 0 && this->d < 0) {
        return false;
    }
    return this->n < 0 || this->d < 0;
}

[[maybe_unused]] [[nodiscard]] bool rational_t::is_positive() const {
    return !is_negative();
}

[[maybe_unused]] [[nodiscard]] bool rational_t::is_zero() const {
    if(!is_consistent(*this)) {
        throw div_by_zero();
    }
    return this->n == 0;
}

[[maybe_unused]] void rational_t::get_to_same_denominator(rational_t::value_t &n_, rational_t::value_t &d_) {
    value_t tmp_d(this->d);
    this->n = n * d_;
    this->d = d * d_;
    n_ = n_ * tmp_d;
    d_ = d_ * tmp_d;
}

[[maybe_unused]] [[nodiscard]] bool rational_t::is_consistent(const rational_t &src) const {
    return d!=0;
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::add(const rational_t &o) {
    if(is_consistent(*this) && is_consistent(o)) {
        value_t tmp_n(o.n);
        value_t tmp_d(o.d);
        if(tmp_d != this->d) {
            get_to_same_denominator(tmp_n, tmp_d);
        }
        this->n = this->n + tmp_n;
    } else {
        throw div_by_zero();
    }
    return *this;
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::sub(const rational_t &o) {
    if(is_consistent(*this) && is_consistent(o)) {
        value_t tmp_n(o.n);
        value_t tmp_d(o.d);
        get_to_same_denominator(tmp_n, tmp_d);
        this->n = this->n - tmp_n;
    } else {
        throw div_by_zero();
    }
    return *this;
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::mul(const rational_t &o) {
    if(is_consistent(*this) && is_consistent(o)) {
        this->n = this->n * o.n;
        this->d = this->d * o.d;
    } else {
        throw div_by_zero();
    }
    return *this;
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::div(const rational_t &o) {
    if(is_consistent(*this) && is_consistent(o)) {
        this->n = this->n * o.d;
        this->d = this->d * o.n;
    } else {
        throw div_by_zero();
    }
    return *this;
}

[[maybe_unused]] [[nodiscard]] rational_t &rational_t::operator=(const rational_t &o) {
    if(is_consistent(*this) && is_consistent(o)) {
        if(this != &o) {
            this->n = o.n;
            this->d = o.d;
        }
    } else {
        throw div_by_zero();
    }
    return *this;
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator+(const rational_t &o) const {
    rational_t tmp(n, d);
    return tmp.add(o);
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator+=(const rational_t &o) {
    return add(o);
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator-(const rational_t &o) const {
    rational_t tmp(n, d);
    return tmp.sub(o);
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator-=(const rational_t &o) {
    return sub(o);
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator*(const rational_t &o) const {
    rational_t tmp(n, d);
    return tmp.mul(o);
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator*=(const rational_t &o) {
    return mul(o);
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator/(const rational_t &o) const {
    rational_t tmp(n, d);
    return tmp.mul(o);
}

[[maybe_unused]] [[nodiscard]] rational_t rational_t::operator/=(const rational_t &o) {
    return div(o);
}

[[maybe_unused]] [[nodiscard]] bool rational_t::equals(const rational_t &o) const {
    return this->n == o.n && this->d == o.d;
}

[[maybe_unused]] [[nodiscard]] bool rational_t::unequals(const rational_t &o) const {
    return !this->equals(o);
}

[[maybe_unused]] [[nodiscard]] bool rational_t::bigger(const rational_t &o) const {
    return this->normalize() > o.normalize();
}

[[maybe_unused]] [[nodiscard]] bool rational_t::smaller(const rational_t &o) const {
    return this->normalize() < o.normalize();
}

[[maybe_unused]] [[nodiscard]] bool rational_t::equals_bigger(const rational_t &o) const {
    return equals(o) || bigger(o);
}

[[maybe_unused]] [[nodiscard]] bool rational_t::equals_smaller(const rational_t &o) const {
    return equals(o) || smaller(o);
}

//non-member functions
[[maybe_unused]] [[nodiscard]] rational_t operator+(const int &o, rational_t &r) {
    rational_t tmp(o);
    return r + tmp;
}

[[maybe_unused]] [[nodiscard]] rational_t operator-(const int &o, rational_t &r) {
    rational_t tmp(o);
    return r - tmp;
}

[[maybe_unused]] [[nodiscard]] rational_t operator*(const int &o, rational_t &r) {
    rational_t tmp(o);
    return r * tmp;
}

[[maybe_unused]] [[nodiscard]] rational_t operator/(const int &o, rational_t &r) {
    rational_t tmp(o);
    return tmp / r;
}

[[maybe_unused]] [[nodiscard]] std::ostream &operator<<(std::ostream &lhs, const rational_t &r) {
    return r.print(lhs);
}

[[maybe_unused]] [[nodiscard]] std::istream &operator>>(std::istream &lhs, rational_t &r) {
    return r.scan(lhs);
}