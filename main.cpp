#include <iostream>

#include "bigint.h"

int main() {
    BigInt i("347895623478956465245892645646249623469234656234756278945629234234");
    std::cout << i.toString() << "\n";
    i.dump();

    return 0;
}
