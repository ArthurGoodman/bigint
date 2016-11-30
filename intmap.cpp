#include "intmap.h"

void IntMap::insert(const BigInt &key, const BigInt &value) {
    set.insert(pair(key, value));
}

BigInt IntMap::get(const BigInt &key) const {
    return unpair(set.get(pair(key, 0))).second;
}

void IntMap::dump() const {
    set.dump();
}
