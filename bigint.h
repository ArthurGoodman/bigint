#pragma once

#include <string>
#include <vector>

typedef unsigned int uint;
typedef unsigned long long ulong;

class BigInt {
    static const uint Base = 1e9;
    static const int DecimalDigitsPerBigDigit = 9;

    std::vector<uint> data;

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
    BigInt operator*(uint x) const;
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

    void dump() const;
};
