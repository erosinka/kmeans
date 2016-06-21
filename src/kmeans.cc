#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "misc.h"
#include "point.h"
#include "algo.h"
#include "cluster.h"


void gen_input(char *filename, int cloud_size) {
    std::ofstream ofs;
    ofs.open(filename);
    if (!ofs.is_open()){
        std::cerr << "cannot open output file\n";
        exit(1);
    }
    kmean::random_generator rg(-100, 100, cloud_size);
    for (int i = 0; i < cloud_size; ++i) {
        kmean::point<float> tmp(rg()*0.01, rg()*0.01, rg()*0.01);
        //kmean::point<float> tmp(rg(), rg(), 0);
        ofs << tmp;
    }
    std::cerr << "gen_input\n";
    ofs.close();
}

int main (int argc, char *argv[]) {
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        std::cout << "This program performs a k-means clustering on a point cloud.\n Run code: kmeans /path/to/point/cloud k\n where k - number of clusters.\n";
        return 0;
    }

    if (argc != 3) {
        std::cout << "Use --help for instructions.\n";
        return 0;
    }
    //gen_input(argv[1], 100);
    kmean::cloud<float> test;
    std::fstream fs;
    fs.open(argv[1]);
    if (!fs.is_open()) {
        std::cerr << "cannot open input file\n";
        exit(1);
    }
    fs >> test;
    fs.close();

    test.clusterize(atoi(argv[2]));
    test.print_centroids(std::cout);
/*
    std::ofstream ofs;
    ofs.open("out.txt");
    if (!ofs.is_open()){
        std::cerr << "cannot open output file\n";
        exit(1);
    }
    test.print_assignment(ofs);
    ofs.close();
*/
    return 0;
}
