#ifndef ALGO
#define ALGO

#include <cmath>
#include <vector>
#include <limits>
#include "point.h"

namespace kmean {

template <typename T>
T dist_euclid (const point<T> & first, const point<T> & second) {
    T tmp = (first.get_x() - second.get_x()) * (first.get_x() - second.get_x()); 
    tmp += (first.get_y() - second.get_y()) * (first.get_y() - second.get_y());
    tmp += (first.get_z() - second.get_z()) * (first.get_z() - second.get_z());
    //return std::sqrt(tmp);
    // sqrt is not really needed as dist is monotonic
    return tmp;
}

template <typename T>
int find_closest_point(const point<T> & p, const std::vector<point<T> > & p_vector) {
    int min_index = -1;
    int pvsize = p_vector.size(); 
    T min_dist = std::numeric_limits<T>::max();

    for (int i = 0; i < pvsize; ++i) {
        T cur_dist = dist_euclid(p, p_vector[i]);
        if (cur_dist < min_dist) {
            min_index = i;
            min_dist = cur_dist; 
        }
    }
    return min_index;
}

template <typename T>
point<T> find_cluster_center(const std::vector<point<T> > & points, const std::vector<int> & point2cluster, int cluster_ind) {
    point<T> new_centroid;
    int cluster_size = 0;
    int psize = points.size();
    for (int i = 0; i < psize; ++i) {
        if (point2cluster[i] == cluster_ind) {
            cluster_size++;
            new_centroid = new_centroid + points[i];
        }
    }
    new_centroid = new_centroid / cluster_size; 
    return new_centroid;
}

}
#endif
