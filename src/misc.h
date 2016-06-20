#include <random>

#ifndef MISC
#define MISC

namespace kmean {
class random_generator {
        //int min, max;
        // initialize a random generator
        std::random_device rd;
        std::mt19937 gen; //(rd());
        std::uniform_int_distribution<> dist; //(min, max);
//        auto dice = std::bind ( distribution, generator );
    public:
        random_generator(int a, int b, int seed): gen(seed), dist(a, b) {};

        int operator()() {
            return dist(gen);
        }
};

}

#endif
