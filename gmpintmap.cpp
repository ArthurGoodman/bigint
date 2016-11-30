#include "GMPIntMap.h"

void GMPIntMap::insert(mpz_t key, mpz_t value) {
    mpz_t p;
    mpz_init(p);

    pair(key, value, p);

    set.insert(p);

    mpz_clear(p);
}

void GMPIntMap::get(mpz_t key, mpz_t r) const {
    mpz_t p, t, x, z;
    mpz_init(p);
    mpz_init(t);
    mpz_init(x);
    mpz_init(z);

    pair(key, z, p);

    set.get(p, t);

    unpair(x, r, t);

    mpz_clear(p);
    mpz_clear(t);
    mpz_clear(x);
    mpz_clear(z);
}

void GMPIntMap::dump() const {
    set.dump();
}
