#include "bigint.h"

#include <sstream>
#include <cmath>

BigInt::BigInt()
    : value(0) {
}

BigInt::BigInt(ulong x) {
    *this = x;
}

BigInt::BigInt(const std::string &str) {
    *this = str;
}

BigInt::BigInt(const BigInt &x) {
    *this = x;
}

BigInt::BigInt(BigInt &&x) {
    *this = std::move(x);
}

BigInt &BigInt::operator=(ulong x) {
    value = x;
    return *this;
}

BigInt &BigInt::operator=(const std::string &str) {
    value = 0;
    ulong t = 1;

    for (std::string::const_reverse_iterator i = str.rbegin(); i != str.rend(); ++i) {
        value += t * (*i - '0');
        t *= 10;
    }

    return *this;
}

BigInt &BigInt::operator=(const BigInt &x) {
    value = x.value;
    return *this;
}

BigInt &BigInt::operator=(BigInt &&x) {
    value = x.value;
    return *this;
}

bool BigInt::operator==(const BigInt &x) const {
    return value == x.value;
}

bool BigInt::operator!=(const BigInt &x) const {
    return value != x.value;
}

bool BigInt::operator<(const BigInt &x) const {
    return value < x.value;
}

bool BigInt::operator<=(const BigInt &x) const {
    return value <= x.value;
}

bool BigInt::operator>(const BigInt &x) const {
    return value > x.value;
}

bool BigInt::operator>=(const BigInt &x) const {
    return value >= x.value;
}

BigInt BigInt::operator+(const BigInt &x) const {
    return value + x.value;
}

BigInt BigInt::operator-(const BigInt &x) const {
    return value - x.value;
}

BigInt BigInt::operator*(const BigInt &x) const {
    return value * x.value;
}

BigInt BigInt::operator/(const BigInt &x) const {
    return value / x.value;
}

BigInt BigInt::operator%(const BigInt &x) const {
    return value % x.value;
}

BigInt &BigInt::operator+=(const BigInt &x) {
    *this = *this + x;
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &x) {
    *this = *this - x;
    return *this;
}

BigInt &BigInt::operator*=(const BigInt &x) {
    *this = *this * x;
    return *this;
}

BigInt &BigInt::operator/=(const BigInt &x) {
    *this = *this / x;
    return *this;
}

BigInt &BigInt::operator%=(const BigInt &x) {
    *this = *this % x;
    return *this;
}

BigInt BigInt::pow(ulong x) const {
    return ::pow(value, x);
}

BigInt BigInt::pow(const BigInt &x) const {
    return ::pow(value, x.value);
}

std::string BigInt::toString() const {
    std::stringstream stream;
    stream << value;
    return stream.str();
}
