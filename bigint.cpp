#include "bigint.h"

BigInt::BigInt() {
}

BigInt::BigInt(ulong x) {
}

BigInt::BigInt(const BigInt &x) {
    *this = x;
}

BigInt::BigInt(BigInt &&x) {
    *this = std::move(x);
}

BigInt &BigInt::operator=(const BigInt &x) {
    data = x.data;
    return *this;
}

BigInt &BigInt::operator=(BigInt &&x) {
    data = std::move(x.data);
    return *this;
}

BigInt BigInt::operator+(const BigInt &x) {
    BigInt result(*this);
    result += x;
    return result;
}

BigInt BigInt::operator-(const BigInt &x) {
    BigInt result(*this);
    result -= x;
    return result;
}

BigInt BigInt::operator*(const BigInt &x) {
    BigInt result(*this);
    result *= x;
    return result;
}

BigInt BigInt::operator/(const BigInt &x) {
    BigInt result(*this);
    result /= x;
    return result;
}

BigInt BigInt::operator%(const BigInt &x) {
    BigInt result(*this);
    result %= x;
    return result;
}

BigInt &BigInt::operator+=(const BigInt &x) {
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &x) {
    return *this;
}

BigInt &BigInt::operator*=(const BigInt &x) {
    return *this;
}

BigInt &BigInt::operator/=(const BigInt &x) {
    return *this;
}

BigInt &BigInt::operator%=(const BigInt &x) {
    return *this;
}

BigInt BigInt::pow(ulong x) {
    return *this;
}

BigInt BigInt::pow(const BigInt &x) {
    return *this;
}
