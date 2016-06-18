#include <iostream>
#include "point.h"
#include "algo.h"


int main (int argc, char *argv[]) {
    kmean::point a, b;
    std::cout << "first point:\n";
    std::cin >> a;
    std::cout << "second point:\n";
    std::cin >> b;
    std::cout << dist_euclid(a, b);
    std::cout << "Hello world!\n"; 
    return 0;
}
