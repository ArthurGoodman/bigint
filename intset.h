#pragma once

#include "bigint.h"
#include "pairing.h"

typedef bool (*Comparator)(const BigInt &a, const BigInt &b);

static bool defaultComparator(const BigInt &a, const BigInt &b) {
    return a < b;
}

template <Comparator less = defaultComparator>
class IntSet {
    BigInt data;

public:
    IntSet();
    IntSet(const IntSet &heap);
    IntSet(IntSet &&heap);

    void insert(const BigInt &value);
    BigInt get(const BigInt &value) const;

    void dump() const;

private:
    BigInt packThree(const BigInt &a, const BigInt &b, const BigInt &c) const;
    std::vector<BigInt> unpackThree(const BigInt &v) const;

    BigInt insert(const BigInt &node, const BigInt &value) const;
    BigInt find(const BigInt &node, const BigInt &value) const;

    void print(const BigInt &node, int indent) const;
};

template <Comparator less>
IntSet<less>::IntSet() {
}

template <Comparator less>
IntSet<less>::IntSet(const IntSet &heap)
    : data(heap.data) {
}

template <Comparator less>
IntSet<less>::IntSet(IntSet &&heap)
    : data(std::move(heap.data)) {
}

template <Comparator less>
void IntSet<less>::insert(const BigInt &value) {
    data = insert(data, value);
}

template <Comparator less>
BigInt IntSet<less>::get(const BigInt &value) const {
    return find(data, value);
}

template <Comparator less>
void IntSet<less>::dump() const {
    std::cout << data << "\n\n";
    print(data, 0);
}

template <Comparator less>
BigInt IntSet<less>::packThree(const BigInt &a, const BigInt &b, const BigInt &c) const {
    return pair(a, pair(b, c));
}

template <Comparator less>
std::vector<BigInt> IntSet<less>::unpackThree(const BigInt &v) const {
    const std::pair<BigInt, BigInt> &ax = unpair(v);
    const std::pair<BigInt, BigInt> &bc = unpair(ax.second);
    return {ax.first, bc.first, bc.second};
}

template <Comparator less>
BigInt IntSet<less>::insert(const BigInt &node, const BigInt &value) const {
    std::vector<BigInt> nodeData = unpackThree(node);

    if (node == 0)
        return packThree(value + 1, 0, 0);
    else if (!less(value, nodeData[0] - 1) && !less(nodeData[0] - 1, value))
        return packThree(value + 1, nodeData[1], nodeData[2]);
    else if (less(value, nodeData[0] - 1))
        return packThree(nodeData[0], insert(nodeData[1], value), nodeData[2]);
    else
        return packThree(nodeData[0], nodeData[1], insert(nodeData[2], value));
}

template <Comparator less>
BigInt IntSet<less>::find(const BigInt &node, const BigInt &value) const {
    std::vector<BigInt> nodeData = unpackThree(node);

    if (node == 0)
        return 0;
    else if (!less(value, nodeData[0] - 1) && !less(nodeData[0] - 1, value))
        return nodeData[0] - 1;
    else if (less(value, nodeData[0] - 1))
        return find(nodeData[1], value);
    else
        return find(nodeData[2], value);
}

template <Comparator less>
void IntSet<less>::print(const BigInt &node, int indent) const {
    if (node == 0) {
        std::cout << std::string(indent, ' ') << "-\n";
        return;
    }

    std::vector<BigInt> nodeData = unpackThree(node);

    std::cout << std::string(indent, ' ') << nodeData[0] - 1 << "\n";

    print(nodeData[1], indent + 1);
    print(nodeData[2], indent + 1);
}
