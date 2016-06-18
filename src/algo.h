#include <cmath>
#include "point.h"

using namespace kmean;

float dist_euclid (point first, point second) {
    if (first == second)
        return 0.0;
    float tmp = pow(first.get_x() - second.get_x(), 2);
    tmp += pow(first.get_y() - second.get_y(), 2);
    tmp += pow(first.get_z() - second.get_z(), 2);
    return sqrt(tmp);

}

template <class T>
T pow(T base, int pow) {
    T tmp = base;
    for (int i = 0; i < pow; i++)
        tmp = tmp * base;
    return tmp;
}


