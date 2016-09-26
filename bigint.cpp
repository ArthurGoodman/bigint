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

    normalize();

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
        uint sum = (i < data.size() ? data[i] : 0) + (i < x.data.size() ? x.data[i] : 0) + carry;
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

    minuend.normalize();

    return minuend;
}

BigInt BigInt::operator*(const BigInt &x) const {
    if (x == 0 || data.empty())
        return BigInt();

    BigInt result = x * data[0];

    for (uint i = 1; i < data.size(); i++) {
        BigInt temp = x * data[i];

        if (!temp.data.empty())
            temp.data.insert(temp.data.begin(), i, 0);

        result += temp;
    }

    return result;
}

BigInt BigInt::operator*(uint x) const {
    if (x == 0 || data.empty())
        return BigInt();

    BigInt result(*this);

    ulong carry = 0;

    for (uint i = 0; i < result.data.size(); i++) {
        ulong temp = (ulong)result.data[i] * x + carry;
        result.data[i] = temp % Base;
        carry = temp / Base;
    }

    if (carry > 0)
        result.data.push_back(carry);

    return result;
}

BigInt BigInt::operator/(const BigInt &x) const {
    return divide(x).first;
}

BigInt BigInt::operator%(const BigInt &x) const {
    return divide(x).second;
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

BigInt &BigInt::operator++() {
    return *this += 1;
}

BigInt BigInt::operator++(int) {
    BigInt result = *this;
    ++*this;
    return result;
}

BigInt &BigInt::operator--() {
    return *this -= 1;
}

BigInt BigInt::operator--(int) {
    BigInt result = *this;
    --*this;
    return result;
}

BigInt BigInt::sqrt() const {
    BigInt hi(*this);
    BigInt lo;

    BigInt mid = (hi + lo) / 2;
    BigInt mid2 = mid * mid;

    while (lo < hi - 1 && mid2 != *this) {
        if (mid2 < *this)
            lo = mid;
        else
            hi = mid;

        mid = (hi + lo) / 2;
        mid2 = mid * mid;
    }

    return mid;
}

std::string BigInt::toString() const {
    if (data.empty())
        return "0";

    std::stringstream stream;

    stream << data.back();

    for (int i = data.size() - 2; i >= 0; i--)
        stream << std::string(DecimalDigitsPerBigDigit - (data[i] == 0 ? 1 : (int)log10(data[i]) + 1), '0') << data[i];

    return stream.str();
}

std::pair<BigInt, BigInt> BigInt::divide(const BigInt &x) const {
    if (x.data.empty())
        throw std::runtime_error("division by zero");

    if (data.empty())
        return std::make_pair(BigInt(), BigInt());

    //    BigInt q, r = *this;

    //    while (r >= x) {
    //        q++;
    //        r -= x;
    //    }

    //    return std::make_pair(q, r);

    if (x.data.size() == 1) {
        BigInt q, r;

        q.data.resize(data.size());
        r.data.resize(1);

        ulong carry = 0;

        for (int j = data.size() - 1; j >= 0; j--) {
            q.data[j] = (carry * Base + data[j]) / x.data[0];
            carry = (carry * Base + data[j]) - (ulong)q.data[j] * x.data[0];
        }

        r.data[0] = carry;

        q.normalize();

        return std::make_pair(q, r);
    }

    return std::make_pair(BigInt(), BigInt());
}

std::ostream &operator<<(std::ostream &stream, const BigInt &x) {
    stream << x.toString();
    return stream;
}

void BigInt::normalize() {
    for (int i = data.size() - 1; i >= 0 && data[i] == 0; i--)
        data.pop_back();
}

#include <iostream>

void BigInt::dump() const {
    std::cout << "{ ";

    for (uint i : data)
        std::cout << i << " ";

    std::cout << "}\n";
}
