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

BigInt modPair(const BigInt &x, const BigInt &y, const BigInt &mod) {
    return mod * y + x;
}

std::pair<BigInt, BigInt> modUnpair(const BigInt &z, const BigInt &mod) {
    const std::pair<BigInt, BigInt> &qr = z.divide(mod);
    return std::make_pair(qr.second, qr.first);
}

BigInt pairVector(const std::vector<BigInt> &vector) {
    BigInt res = vector.back();

    for (int i = vector.size() - 2; i >= 0; i--)
        res = pair(vector[i], res);

    return res;
}

std::vector<BigInt> unpairVector(BigInt z, int size) {
    std::vector<BigInt> vector;

    for (int i = 0; i < size - 1; i++) {
        const std::pair<BigInt, BigInt> &xy = unpair(z);
        vector.push_back(xy.first);
        z = xy.second;
    }

    vector.push_back(z);

    return vector;
}

BigInt modPairVector(const std::vector<BigInt> &vector, const BigInt &mod) {
    BigInt res = vector.back();

    for (int i = vector.size() - 2; i >= 0; i--)
        res = modPair(vector[i], res, mod);

    return res;
}

std::vector<BigInt> modUnpairVector(BigInt z, int size, const BigInt &mod) {
    std::vector<BigInt> vector;

    for (int i = 0; i < size - 1; i++) {
        const std::pair<BigInt, BigInt> &xy = modUnpair(z, mod);
        vector.push_back(xy.first);
        z = xy.second;
    }

    vector.push_back(z);

    return vector;
}

BigInt pairTree(const std::vector<BigInt> &vector) {
    if (vector.empty())
        return (ulong)0;

    if (vector.size() == 1)
        return vector.back();

    if (vector.size() == 2)
        return pair(vector[0], vector[1]);

    if (vector.size() == 3)
        return pair(vector[0], pair(vector[1], vector[2]));

    std::vector<BigInt> lo, hi;
    int i = 0;

    for (; i < (int)vector.size() / 2; i++)
        lo.push_back(vector[i]);

    for (; i < (int)vector.size(); i++)
        hi.push_back(vector[i]);

    return pair(pairTree(lo), pairTree(hi));
}

std::vector<BigInt> unpairTree(const BigInt &z, int size) {
    if (size == 0)
        return {};

    if (size == 1)
        return {z};

    const std::pair<BigInt, BigInt> &pair = unpair(z);

    if (size == 2)
        return {pair.first, pair.second};

    if (size == 3) {
        const std::pair<BigInt, BigInt> &temp = unpair(pair.second);
        return {pair.first, temp.first, temp.second};
    }

    std::vector<BigInt> lo = unpairTree(pair.first, size / 2), hi = unpairTree(pair.second, size - size / 2);

    std::vector<BigInt> result;

    result.insert(result.end(), lo.begin(), lo.end());
    result.insert(result.end(), hi.begin(), hi.end());

    return result;
}

BigInt modPairTree(const std::vector<BigInt> &vector, const BigInt &mod) {
    if (vector.empty())
        return (ulong)0;

    if (vector.size() == 1)
        return vector.back();

    if (vector.size() == 2)
        return modPair(vector[0], vector[1], mod);

    if (vector.size() == 3)
        return modPair(vector[0], modPair(vector[1], vector[2], mod), mod);

    std::vector<BigInt> lo, hi;
    int i = 0;

    for (; i < (int)vector.size() / 2; i++)
        lo.push_back(vector[i]);

    for (; i < (int)vector.size(); i++)
        hi.push_back(vector[i]);

    return pair(modPairTree(lo, mod), modPairTree(hi, mod));
}

std::vector<BigInt> modUnpairTree(const BigInt &z, int size, const BigInt &mod) {
    if (size == 0)
        return {};

    if (size == 1)
        return {z};

    if (size == 2) {
        const std::pair<BigInt, BigInt> &xy = modUnpair(z, mod);
        return {xy.first, xy.second};
    }

    if (size == 3) {
        const std::pair<BigInt, BigInt> &xw = modUnpair(z, mod);
        const std::pair<BigInt, BigInt> &yz = modUnpair(xw.second, mod);
        return {xw.first, yz.first, yz.second};
    }

    const std::pair<BigInt, BigInt> &xy = unpair(z);

    std::vector<BigInt> lo = modUnpairTree(xy.first, size / 2, mod), hi = modUnpairTree(xy.second, size - size / 2, mod);

    std::vector<BigInt> result;

    result.insert(result.end(), lo.begin(), lo.end());
    result.insert(result.end(), hi.begin(), hi.end());

    return result;
}

BigInt pairTreeWithOtherPartitioning(const std::vector<BigInt> &vector) {
    if (vector.empty())
        return (ulong)0;

    if (vector.size() == 1)
        return vector.back();

    if (vector.size() == 2)
        return pair(vector[0], vector[1]);

    if (vector.size() == 3)
        return pair(vector[0], pair(vector[1], vector[2]));

    std::vector<BigInt> lo, hi;
    int i = 0, loSize = vector.size() / 2 - (vector.size() / 2 % 2 == 0 ? 0 : 1);

    for (; i < loSize; i++)
        lo.push_back(vector[i]);

    for (; i < (int)vector.size(); i++)
        hi.push_back(vector[i]);

    return pair(pairTreeWithOtherPartitioning(lo), pairTreeWithOtherPartitioning(hi));
}

std::vector<BigInt> unpairTreeWithOtherPartitioning(const BigInt &z, int size) {
    if (size == 0)
        return {};

    if (size == 1)
        return {z};

    const std::pair<BigInt, BigInt> &xy = unpair(z);

    if (size == 2)
        return {xy.first, xy.second};

    if (size == 3) {
        const std::pair<BigInt, BigInt> &yz = unpair(xy.second);
        return {xy.first, yz.first, yz.second};
    }

    int loSize = size / 2 - (size / 2 % 2 == 0 ? 0 : 1);

    std::vector<BigInt> lo = unpairTreeWithOtherPartitioning(xy.first, loSize), hi = unpairTreeWithOtherPartitioning(xy.second, size - loSize), result;

    result.insert(result.end(), lo.begin(), lo.end());
    result.insert(result.end(), hi.begin(), hi.end());

    return result;
}

BigInt modPairTreeWithOtherPartitioning(const std::vector<BigInt> &vector, const BigInt &mod) {
    if (vector.empty())
        return (ulong)0;

    if (vector.size() == 1)
        return vector.back();

    if (vector.size() == 2)
        return modPair(vector[0], vector[1], mod);

    if (vector.size() == 3)
        return modPair(vector[0], modPair(vector[1], vector[2], mod), mod);

    std::vector<BigInt> lo, hi;
    int i = 0, loSize = vector.size() / 2 - (vector.size() / 2 % 2 == 0 ? 0 : 1);

    for (; i < loSize; i++)
        lo.push_back(vector[i]);

    for (; i < (int)vector.size(); i++)
        hi.push_back(vector[i]);

    return pair(modPairTreeWithOtherPartitioning(lo, mod), modPairTreeWithOtherPartitioning(hi, mod));
}

std::vector<BigInt> modUnpairTreeWithOtherPartitioning(const BigInt &z, int size, const BigInt &mod) {
    if (size == 0)
        return {};

    if (size == 1)
        return {z};

    if (size == 2) {
        const std::pair<BigInt, BigInt> &xy = modUnpair(z, mod);
        return {xy.first, xy.second};
    }

    if (size == 3) {
        const std::pair<BigInt, BigInt> &xw = modUnpair(z, mod);
        const std::pair<BigInt, BigInt> &yz = modUnpair(xw.second, mod);
        return {xw.first, yz.first, yz.second};
    }

    const std::pair<BigInt, BigInt> &xy = unpair(z);

    int loSize = size / 2 - (size / 2 % 2 == 0 ? 0 : 1);

    std::vector<BigInt> lo = modUnpairTreeWithOtherPartitioning(xy.first, loSize, mod), hi = modUnpairTreeWithOtherPartitioning(xy.second, size - loSize, mod), result;

    result.insert(result.end(), lo.begin(), lo.end());
    result.insert(result.end(), hi.begin(), hi.end());

    return result;
}

template <class T>
void printVector(const std::vector<T> &vector) {
    for (T x : vector)
        std::cout << x << " ";
}

int main() {
    std::vector<BigInt> vector = {3, 157, 84, 214, 128, 197, 38, 140, 91, 44};

    BigInt x = pairVector(vector);
    std::cout << x << "\n";
    printVector(unpairVector(x, vector.size()));
    std::cout << "\n\n";

    x = modPairVector(vector, 256);
    std::cout << x << "\n";
    printVector(modUnpairVector(x, vector.size(), 256));
    std::cout << "\n\n";

    x = pairTree(vector);
    std::cout << x << "\n";
    printVector(unpairTree(x, vector.size()));
    std::cout << "\n\n";

    x = modPairTree(vector, 256);
    std::cout << x << "\n";
    printVector(modUnpairTree(x, vector.size(), 256));
    std::cout << "\n\n";

    x = pairTreeWithOtherPartitioning(vector);
    std::cout << x << "\n";
    printVector(unpairTreeWithOtherPartitioning(x, vector.size()));
    std::cout << "\n\n";

    x = modPairTreeWithOtherPartitioning(vector, 256);
    std::cout << x << "\n";
    printVector(modUnpairTreeWithOtherPartitioning(x, vector.size(), 256));
    std::cout << "\n\n";

    return 0;
}
