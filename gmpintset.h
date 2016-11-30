#pragma once

#include "gmppairing.h"
#include <iostream>

typedef bool (*Comparator)(const mpz_t a, const mpz_t b);

static bool defaultComparator(const mpz_t a, const mpz_t b) {
    return mpz_cmp(a, b) < 0;
}

template <Comparator less = defaultComparator>
class GMPIntSet {
    mpz_t data;

public:
    GMPIntSet();
    GMPIntSet(const GMPIntSet &set);

    void insert(mpz_t value);
    void get(mpz_t value, mpz_t r) const;

    void dump() const;

private:
    void packThree(const mpz_t a, const mpz_t b, const mpz_t c, mpz_t r) const;
    void unpackThree(mpz_t a, mpz_t b, mpz_t c, const mpz_t r) const;

    void insert(const mpz_t node, const mpz_t value, mpz_t r) const;
    void find(const mpz_t node, const mpz_t value, mpz_t r) const;

    void print(const mpz_t node, int indent) const;
};

template <Comparator less>
GMPIntSet<less>::GMPIntSet() {
    mpz_init(data);
}

template <Comparator less>
GMPIntSet<less>::GMPIntSet(const GMPIntSet &set) {
    mpz_init_set(data, set.data);
}

template <Comparator less>
void GMPIntSet<less>::insert(mpz_t value) {
    mpz_t temp;
    mpz_init(temp);
    insert(data, value, temp);
    mpz_set(data, temp);
    mpz_clear(temp);
}

template <Comparator less>
void GMPIntSet<less>::get(mpz_t value, mpz_t r) const {
    find(data, value, r);
}

template <Comparator less>
void GMPIntSet<less>::dump() const {
    std::cout << mpz_get_str(0, 10, data) << "\n\n";
    print(data, 0);
}

template <Comparator less>
void GMPIntSet<less>::packThree(const mpz_t a, const mpz_t b, const mpz_t c, mpz_t r) const {
    mpz_t temp;
    mpz_init(temp);
    pair(b, c, temp);
    pair(a, temp, r);
    mpz_clear(temp);
}

template <Comparator less>
void GMPIntSet<less>::unpackThree(mpz_t a, mpz_t b, mpz_t c, const mpz_t r) const {
    unpair(a, b, r);
    unpair(b, c, b);
}

template <Comparator less>
void GMPIntSet<less>::insert(const mpz_t node, const mpz_t value, mpz_t r) const {
    mpz_t a, b, c;
    mpz_init(a);
    mpz_init(b);
    mpz_init(c);

    unpackThree(a, b, c, node);

    mpz_t aSub1;
    mpz_init(aSub1);
    mpz_sub_ui(aSub1, a, 1);

    if (mpz_cmp_ui(node, 0) == 0) {
        mpz_add_ui(a, value, 1);
        mpz_set_ui(b, 0);
        mpz_set_ui(c, 0);
        packThree(a, b, c, r);
    } else if (!less(value, aSub1) && !less(aSub1, value)) {
        mpz_add_ui(a, value, 1);
        packThree(a, b, c, r);
    } else if (less(value, aSub1)) {
        mpz_t temp;
        mpz_init(temp);
        insert(b, value, temp);
        packThree(a, temp, c, r);
        mpz_clear(temp);
    } else {
        mpz_t temp;
        mpz_init(temp);
        insert(c, value, temp);
        packThree(a, b, temp, r);
        mpz_clear(temp);
    }

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    mpz_clear(aSub1);
}

template <Comparator less>
void GMPIntSet<less>::find(const mpz_t node, const mpz_t value, mpz_t r) const {
    mpz_t a, b, c;
    mpz_init(a);
    mpz_init(b);
    mpz_init(c);

    unpackThree(a, b, c, node);

    mpz_t aSub1;
    mpz_init(aSub1);
    mpz_sub_ui(aSub1, a, 1);

    if (mpz_cmp_ui(node, 0) == 0)
        mpz_set_ui(r, 0);
    else if (!less(value, aSub1) && !less(aSub1, value))
        mpz_sub_ui(r, a, 1);
    else if (less(value, aSub1))
        find(b, value, r);
    else
        find(c, value, r);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    mpz_clear(aSub1);
}

template <Comparator less>
void GMPIntSet<less>::print(const mpz_t node, int indent) const {
    if (mpz_cmp_ui(node, 0) == 0) {
        std::cout << std::string(indent, ' ') << "-\n";
        return;
    }

    mpz_t a, b, c;
    mpz_init(a);
    mpz_init(b);
    mpz_init(c);

    unpackThree(a, b, c, node);

    mpz_t aSub1;
    mpz_init(aSub1);
    mpz_sub_ui(aSub1, a, 1);

    std::cout << std::string(indent, ' ') << mpz_get_str(0, 10, aSub1) << "\n";

    print(b, indent + 1);
    print(c, indent + 1);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    mpz_clear(aSub1);
}
