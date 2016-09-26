#include "pairing.h"

#include "intmap.h"

int main() {
    IntMap map;

    map.insert(2, 222);
    map.insert(1, 111);
    map.insert(5, 555);
    map.insert(4, 444);
    map.insert(3, 333);

    std::cout << map.get(1) << "\n";
    std::cout << map.get(2) << "\n";
    std::cout << map.get(3) << "\n";
    std::cout << map.get(4) << "\n";
    std::cout << map.get(5) << "\n";

    std::cout << "\n";

    map.dump();

    return 0;
}
