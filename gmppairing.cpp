#include "gmppairing.h"

void pair(const mpz_t x, const mpz_t y, mpz_t z) {
    mpz_t t;
    mpz_init(t);

    mpz_add(t, x, y);

    mpz_set(z, t);
    mpz_add_ui(z, z, 1);

    mpz_mul(z, z, t);
    mpz_div_ui(z, z, 2);

    mpz_add(z, z, y);

    mpz_clear(t);
}

void unpair(mpz_t x, mpz_t y, const mpz_t z) {
    mpz_t w, t;
    mpz_init(w);
    mpz_init(t);

    mpz_mul_ui(w, z, 8);
    mpz_add_ui(w, w, 1);
    mpz_sqrt(w, w);
    mpz_sub_ui(w, w, 1);
    mpz_div_ui(w, w, 2);

    mpz_mul(t, w, w);
    mpz_add(t, t, w);
    mpz_div_ui(t, t, 2);

    mpz_sub(y, z, t);
    mpz_sub(x, w, y);

    mpz_clear(w);
    mpz_clear(t);
}
