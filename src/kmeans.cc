#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "misc.h"
#include "point.h"
#include "algo.h"
#include "cluster.h"

int main (int argc, char *argv[]) {
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        std::cout << "This program performs a k-means clustering on a point cloud.\n Run code: kmeans /path/to/point/cloud k\n where k - number of clusters.\n";
        return 0;
    }

    if (argc != 3) {
        std::cout << "Use --help for instructions.\n";
        return 0;
    }

//    cloud test(argv[2].to_i());
    kmean::cloud test;
    std::fstream fs;
    fs.open(argv[1]);
    if (!fs.is_open()) {
        std::cerr << "cannot open input file\n";
        exit(1);
    }
    fs >> test;
    std::cout << test;
    fs.close();
    test.clusterize(atoi(argv[2]));
    kmean::point a, b;
    std::cout << "first point:\n";
    std::cin >> a;
    std::cout << "second point:\n";
    std::cin >> b;
    std::cout << dist_euclid(a, b) << std::endl;
    return 0;
}
