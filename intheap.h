#pragma once

#include "bigint.h"

typedef bool (*Comparator)(const BigInt &a, const BigInt &b);

bool defaultComparator(const BigInt &a, const BigInt &b) {
    return a < b;
}

template <Comparator less = defaultComparator>
class IntHeap {
    BigInt data;

public:
    IntHeap();
    IntHeap(const IntHeap &heap);
    IntHeap(IntHeap &&heap);

    void insert(const BigInt &value);
    BigInt get(const BigInt &value);

    void dump() const;

private:
    BigInt pair(const BigInt &x, const BigInt &y);
    std::pair<BigInt, BigInt> unpair(const BigInt &z);

    BigInt packThree(const BigInt &a, const BigInt &b, const BigInt &c);
    std::vector<BigInt> unpackThree(const BigInt &v);

    BigInt siftDown(const BigInt &root, const BigInt &value);
    BigInt find(const BigInt &root, const BigInt &value);
};

template <Comparator less>
IntHeap<less>::IntHeap() {
}

template <Comparator less>
IntHeap<less>::IntHeap(const IntHeap &heap)
    : data(heap.data) {
}

template <Comparator less>
IntHeap<less>::IntHeap(IntHeap &&heap)
    : data(std::move(heap.data)) {
}

template <Comparator less>
void IntHeap<less>::insert(const BigInt &value) {
    if (data == 0)
        data = packThree(value, 0, 0);
    else
        data = siftDown(data, value);
}

template <Comparator less>
BigInt IntHeap<less>::get(const BigInt &value) {
    if (data == 0)
        return (ulong)0;
    else
        return find(data, value);
}

template <Comparator less>
void IntHeap<less>::dump() const {
    std::cout << data << "\n";
}

template <Comparator less>
BigInt IntHeap<less>::pair(const BigInt &x, const BigInt &y) {
    return (x + y) * (x + y + 1) / 2 + y;
}

template <Comparator less>
std::pair<BigInt, BigInt> IntHeap<less>::unpair(const BigInt &z) {
    BigInt w = ((z * 8 + 1).sqrt() - 1) / 2;
    BigInt t = (w * w + w) / 2;
    BigInt y = z - t;
    BigInt x = w - y;

    return std::make_pair(x, y);
}

template <Comparator less>
BigInt IntHeap<less>::packThree(const BigInt &a, const BigInt &b, const BigInt &c) {
    return pair(a, pair(b, c));
}

template <Comparator less>
std::vector<BigInt> IntHeap<less>::unpackThree(const BigInt &v) {
    const std::pair<BigInt, BigInt> &ax = unpair(v);
    const std::pair<BigInt, BigInt> &bc = unpair(ax.second);
    return {ax.first, bc.first, bc.second};
}

template <Comparator less>
BigInt IntHeap<less>::siftDown(const BigInt &root, const BigInt &value) {
    const std::vector<BigInt> parent = unpackThree(root);
    const std::vector<BigInt> leftChild = unpackThree(parent[1]);
    const std::vector<BigInt> rightChild = unpackThree(parent[2]);

    if (less(value, parent[0]))
        return siftDown(packThree(value, parent[1], parent[2]), parent[0]);

    if (parent[1] == 0 && parent[2] == 0)
        return packThree(parent[0], packThree(value, 0, 0), 0);

    if (parent[2] == 0) {
        if (less(value, leftChild[0]))
            return packThree(parent[0], packThree(value, 0, 0), parent[1]);
        else
            return packThree(parent[0], parent[1], packThree(value, 0, 0));
    }

    if (less(value, leftChild[0]))
        return packThree(parent[0], siftDown(packThree(value, leftChild[1], leftChild[2]), leftChild[0]), parent[2]);

    if (less(value, rightChild[0]))
        return packThree(parent[0], parent[1], siftDown(packThree(value, rightChild[1], rightChild[2]), rightChild[0]));

    return (ulong)0;
}

template <Comparator less>
BigInt IntHeap<less>::find(const BigInt &root, const BigInt &value) {
    return (ulong)0;
}
