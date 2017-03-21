#include <algorithm>
#include <ctime>
#include <vector>

#include "gmpintmap.h"

int main() {
    GMPIntMap map;

    const int n = 9;

    mpz_t k, v;

    mpz_init(k);
    mpz_init(v);

    std::vector<int> vec(n);
    std::iota(vec.begin(), vec.end(), 1);
    srand(time(0));
    std::random_shuffle(vec.begin(), vec.end());

    for (int i : vec) {
        mpz_set_ui(k, i);
        mpz_set_ui(v, i * 111);
        map.insert(k, v);
    }

    for (unsigned int i = 1; i <= n; i++) {
        mpz_set_ui(k, i);
        map.get(k, v);
        std::cout << mpz_get_str(0, 10, v) << "\n";
    }

    std::cout << "\n";

    map.dump();

    mpz_clear(k);
    mpz_clear(v);

    return 0;
}
