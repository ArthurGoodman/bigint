#pragma once

#include "bigint.h"

void testPairing();

BigInt pair(const BigInt &x, const BigInt &y);
std::pair<BigInt, BigInt> unpair(const BigInt &z);
