#pragma once

#include <string>

typedef unsigned long long ulong;

class BigInt {
    ulong value;

public:
    BigInt();
    BigInt(ulong x);
    BigInt(const std::string &str);
    BigInt(const BigInt &x);
    BigInt(BigInt &&x);

    BigInt &operator=(ulong x);
    BigInt &operator=(const std::string &str);
    BigInt &operator=(const BigInt &x);
    BigInt &operator=(BigInt &&x);

    bool operator==(const BigInt &x) const;
    bool operator!=(const BigInt &x) const;
    bool operator<(const BigInt &x) const;
    bool operator<=(const BigInt &x) const;
    bool operator>(const BigInt &x) const;
    bool operator>=(const BigInt &x) const;

    BigInt operator+(const BigInt &x) const;
    BigInt operator-(const BigInt &x) const;
    BigInt operator*(const BigInt &x) const;
    BigInt operator/(const BigInt &x) const;
    BigInt operator%(const BigInt &x) const;

    BigInt &operator+=(const BigInt &x);
    BigInt &operator-=(const BigInt &x);
    BigInt &operator*=(const BigInt &x);
    BigInt &operator/=(const BigInt &x);
    BigInt &operator%=(const BigInt &x);

    BigInt pow(ulong x) const;
    BigInt pow(const BigInt &x) const;

    std::string toString() const;
};
