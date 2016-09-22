#include <iostream>

#include "bigint.h"

int main() {
    BigInt a("347895623478956465245892645646249623469234656234756278945629234234");
    BigInt b("121571845151578145812851289751289355612898561926517925617945917845");
    BigInt c = a + b;

    std::cout << c.toString() << "\n";

    c.dump();

    return 0;
}
