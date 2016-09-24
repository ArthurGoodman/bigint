#include <iostream>

#include "bigint.h"

int main() {
    BigInt a("364715535454734437438553869253868066838695685779553776853837753535");
    BigInt b("123456789");
    BigInt c = a / b;
    BigInt d = a % b;

    std::cout << a.toString() << "\n";
    std::cout << b.toString() << "\n";
    std::cout << c.toString() << "\n";
    std::cout << d.toString() << "\n";
    std::cout << (b * c + d).toString() << "\n";

    a.dump();
    b.dump();
    c.dump();
    d.dump();

    return 0;
}
