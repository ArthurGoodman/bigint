#pragma once

#include <vector>

typedef unsigned char byte;
typedef unsigned long long ulong;

#define BASE 256

class BigInt {
    std::vector<byte> data;

public:
    BigInt();
    BigInt(ulong x);
    BigInt(const BigInt &x);
    BigInt(BigInt &&x);

    BigInt &operator=(const BigInt &x);
    BigInt &operator=(BigInt &&x);

    BigInt &operator+(const BigInt &x);
    BigInt &operator-(const BigInt &x);
    BigInt &operator*(const BigInt &x);
    BigInt &operator/(const BigInt &x);
    BigInt &operator%(const BigInt &x);

    BigInt &operator+=(const BigInt &x);
    BigInt &operator-=(const BigInt &x);
    BigInt &operator*=(const BigInt &x);
    BigInt &operator/=(const BigInt &x);
    BigInt &operator%=(const BigInt &x);

    BigInt pow(ulong x);
    BigInt pow(const BigInt &x);
};
