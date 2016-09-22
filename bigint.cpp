#include "bigint.h"

#include <sstream>

#include <iostream>

BigInt::BigInt() {
    data.push_back(0);
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
    data.clear();

    do {
        data.push_back(x % Base);
        x /= Base;
    } while (x > 0);

    return *this;
}

BigInt &BigInt::operator=(const std::string &str) {
    data.clear();

    int i;
    std::stringstream stream;

    for (i = str.size() - DecimalDigitsPerBigDigit; i >= 0; i -= DecimalDigitsPerBigDigit) {
        stream << str.substr(i, DecimalDigitsPerBigDigit);

        data.push_back(0);
        stream >> data.back();

        stream.clear();
    }

    if (i > -DecimalDigitsPerBigDigit) {
        stream << str.substr(0, DecimalDigitsPerBigDigit + i);

        data.push_back(0);
        stream >> data.back();
    }

    return *this;
}

BigInt &BigInt::operator=(const BigInt &x) {
    data = x.data;
    return *this;
}

BigInt &BigInt::operator=(BigInt &&x) {
    data = std::move(x.data);
    return *this;
}

bool BigInt::operator==(const BigInt &x) const {
    return true;
}

bool BigInt::operator!=(const BigInt &x) const {
    return true;
}

bool BigInt::operator<(const BigInt &x) const {
    return true;
}

bool BigInt::operator<=(const BigInt &x) const {
    return true;
}

bool BigInt::operator>(const BigInt &x) const {
    return true;
}

bool BigInt::operator>=(const BigInt &x) const {
    return true;
}

BigInt BigInt::operator+(const BigInt &x) const {
    return *this;
}

BigInt BigInt::operator-(const BigInt &x) const {
    return *this;
}

BigInt BigInt::operator*(const BigInt &x) const {
    return *this;
}

BigInt BigInt::operator/(const BigInt &x) const {
    return *this;
}

BigInt BigInt::operator%(const BigInt &x) const {
    return *this;
}

BigInt &BigInt::operator+=(const BigInt &x) {
    return *this = *this + x;
}

BigInt &BigInt::operator-=(const BigInt &x) {
    return *this = *this - x;
}

BigInt &BigInt::operator*=(const BigInt &x) {
    return *this = *this * x;
}

BigInt &BigInt::operator/=(const BigInt &x) {
    return *this = *this / x;
}

BigInt &BigInt::operator%=(const BigInt &x) {
    return *this = *this % x;
}

BigInt BigInt::pow(ulong x) const {
    return *this;
}

BigInt BigInt::pow(const BigInt &x) const {
    return *this;
}

std::string BigInt::toString() const {
    std::stringstream stream;

    stream << data.back();

    for (int i = data.size() - 2; i >= 0; i--)
        stream << data[i];

    return stream.str();
}

void BigInt::dump() const {
    std::cout << "{ ";

    for (uint i : data)
        std::cout << i << " ";

    std::cout << "}\n";
}
