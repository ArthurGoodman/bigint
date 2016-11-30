#pragma once

#include "intset.h"

class IntMap {
    static bool comparator(const BigInt &a, const BigInt &b) {
        return unpair(a).first < unpair(b).first;
    }

    IntSet<comparator> set;

public:
    void insert(const BigInt &key, const BigInt &value);
    BigInt get(const BigInt &key) const;

    void dump() const;
};
