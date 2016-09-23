#include "bigint.h"

#include <sstream>
#include <cmath>

BigInt::BigInt() {
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

    if (x == 0)
        return *this;

    do {
        data.push_back(x % Base);
        x /= Base;
    } while (x > 0);

    return *this;
}

BigInt &BigInt::operator=(const std::string &str) {
    data.clear();

    if (str.empty())
        return *this;

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
    if (data.size() != x.data.size())
        return false;
    else
        for (uint i = 0; i < data.size(); i++)
            if (data[i] != x.data[i])
                return false;

    return true;
}

bool BigInt::operator!=(const BigInt &x) const {
    return !(*this == x);
}

bool BigInt::operator<(const BigInt &x) const {
    if (data.size() < x.data.size())
        return true;
    else if (data.size() > x.data.size())
        return false;
    else
        for (int i = (int)data.size() - 1; i >= 0; i--)
            if (data[i] < x.data[i])
                return true;
            else if (data[i] > x.data[i])
                return false;

    return false;
}

bool BigInt::operator<=(const BigInt &x) const {
    return *this < x || *this == x;
}

bool BigInt::operator>(const BigInt &x) const {
    return !(*this <= x);
}

bool BigInt::operator>=(const BigInt &x) const {
    return !(*this < x);
}

BigInt BigInt::operator+(const BigInt &x) const {
    if (data.empty())
        return x;

    if (x.data.empty())
        return *this;

    BigInt result;
    result.data.resize(std::max(data.size(), x.data.size()));

    uint carry = 0;

    for (uint i = 0; i < result.data.size(); i++) {
        ulong sum = data[i] + x.data[i] + carry;
        result.data[i] = sum % Base;
        carry = sum / Base;
    }

    if (carry > 0)
        result.data.push_back(carry);

    return result;
}

BigInt BigInt::operator-(const BigInt &x) const {
    if (data.empty())
        return x;

    if (x.data.empty())
        return *this;

    BigInt minuend = *this > x ? *this : x;
    const BigInt &subtrahend = *this > x ? x : *this;

    for (uint i = 0; i < minuend.data.size(); i++) {
        uint digit = (i < subtrahend.data.size() ? subtrahend.data[i] : 0);

        if (minuend.data[i] < digit || minuend.data[i] == UINT_MAX) {
            minuend.data[i] += Base;
            minuend.data[i + 1]--;
        }

        minuend.data[i] -= digit;
    }

    for (int i = minuend.data.size() - 1; i >= 0 && minuend.data[i] == 0; i--)
        minuend.data.pop_back();

    return minuend;
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
    if (data.empty())
        return "0";

    std::stringstream stream;

    stream << data.back();

    for (int i = data.size() - 2; i >= 0; i--)
        stream << std::string(DecimalDigitsPerBigDigit - log10(data[i]), '0') << data[i];

    return stream.str();
}

#include <iostream>

void BigInt::dump() const {
    std::cout << "{ ";

    for (uint i : data)
        std::cout << i << " ";

    std::cout << "}\n";
}
