#pragma once

#include "gmpintset.h"

class GMPIntMap {
    static bool comparator(const mpz_t a, const mpz_t b) {
        mpz_t ax, ay, bx, by;
        mpz_init(ax);
        mpz_init(ay);
        mpz_init(bx);
        mpz_init(by);

        unpair(ax, ay, a);
        unpair(bx, by, b);

        bool result = mpz_cmp(ax, bx) < 0;

        mpz_clear(ax);
        mpz_clear(ay);
        mpz_clear(bx);
        mpz_clear(by);

        return result;
    }

    GMPIntSet<comparator> set;

public:
    void insert(mpz_t key, mpz_t value);
    void get(mpz_t key, mpz_t r) const;

    void dump() const;
};
