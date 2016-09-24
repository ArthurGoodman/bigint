#include <iostream>

#include "bigint.h"

BigInt pair(const BigInt &x, const BigInt &y) {
    return (x + y) * (x + y + 1) / 2 + y;
}

std::pair<BigInt, BigInt> unpair(const BigInt &z) {
    BigInt w = ((z * 8 + 1).sqrt() - 1) / 2;
    BigInt t = (w * w + w) / 2;
    BigInt y = z - t;
    BigInt x = w - y;

    return std::make_pair(x, y);
}

BigInt modPair(BigInt x, BigInt y, BigInt mod) {
    return mod * y + x;
}

std::pair<BigInt, BigInt> modUnpair(BigInt z, BigInt mod) {
    std::pair<BigInt, BigInt> result = z.divide(mod);
    return std::make_pair(result.second, result.first);
}

BigInt pairVector(const std::vector<BigInt> &vector) {
    BigInt res = vector.back();

    for (int i = vector.size() - 2; i >= 0; i--)
        res = pair(vector[i], res);

    return res;
}

std::vector<BigInt> unpairVector(BigInt c, int size) {
    std::vector<BigInt> vector;

    for (int i = 0; i < size - 1; i++) {
        std::pair<BigInt, BigInt> pair = unpair(c);
        vector.push_back(pair.first);
        c = pair.second;
    }

    vector.push_back(c);

    return vector;
}

BigInt modPairVector(const std::vector<BigInt> &vector, BigInt mod) {
    BigInt res = vector.back();

    for (int i = vector.size() - 2; i >= 0; i--)
        res = modPair(vector[i], res, mod);

    return res;
}

std::vector<BigInt> modUnpairVector(BigInt c, int size, BigInt mod) {
    std::vector<BigInt> vector;

    for (int i = 0; i < size - 1; i++) {
        std::pair<BigInt, BigInt> pair = modUnpair(c, mod);
        vector.push_back(pair.first);
        c = pair.second;
    }

    vector.push_back(c);

    return vector;
}

template <class T>
void printVector(const std::vector<T> &vector) {
    for (T x : vector)
        std::cout << x << " ";
}

int main() {
    std::vector<BigInt> vector = {(ulong)0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    BigInt x = pairVector(vector);
    std::cout << x << "\n";
    printVector(unpairVector(x, vector.size()));
    std::cout << "\n";

    return 0;
}
