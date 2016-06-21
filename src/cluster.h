#ifndef CLUSTER
#define CLUSTER

#include <iostream>
#include <random>
#include <vector>
#include <cmath>

#include "point.h"
#include "algo.h"
#include "misc.h"

namespace kmean {

template <typename T>
class cloud {
    std::vector<point<T> > points;
    std::vector<point<T> > centroids;
    // vector of cluster id of each point i 
    std::vector<int> point2cluster;
    // number of clusters
    int _cluster_num;
    int _cluster_assign_diff;

    void initialize() {
        // choose randomly k centroids by 
        // shuffling points and then cut-off first clust_num
        centroids.resize(points.size()); 
        std::copy(points.begin(), points.end(), centroids.begin()); 
        std::random_shuffle(centroids.begin(), centroids.end()) ;
        centroids.resize(_cluster_num); 
        point2cluster.resize(points.size());
    }

    // complexity o(n*k)
    void assign_clusters () {
        _cluster_assign_diff = 0;
        int psize = points.size();
        for (int i = 0; i < psize; ++i) { 
            // find index of the centroid closest to the point<T> i
            int new_cluster_id = find_closest_point(points[i], centroids);
            _cluster_assign_diff += ((point2cluster[i] == new_cluster_id) ? 0 : 1);
            point2cluster[i] = new_cluster_id;
        }
    }

    // complexity o(k*n)
    void reassign_centroids() {
        for (int i = 0; i < centroids.size(); ++i) {
            centroids[i] = find_cluster_center(points, point2cluster, i); 
        }
    }

    public:
        cloud() {
            centroids.reserve(constants::reserve_cloud_size);
            point2cluster.reserve(constants::reserve_cloud_size);
            points.reserve(constants::reserve_cloud_size);    
        }


    void clusterize(int k_num)  {
        if (!points.size()) {
            std::cerr << "Cloud is empty.\n";
            exit(1);
        }
        if (k_num <= 0) {
            std::cerr << "Number of clusters should be positive.\n";
            exit(1);
        }
        if (k_num > points.size()) {
            std::cerr << "Number of clusters should not be greater that cloud size.\n";
            exit(1);
        }
        _cluster_num = k_num;
        int iters = 0;
        bool no_change = false;
        initialize();
        do {
            // assign each point<T> to a closest centroid
            assign_clusters();
            reassign_centroids();
            no_change = (_cluster_assign_diff < 1);// constants::eps);
            ++iters;
        // continue UNTIL no change in cluster assign or reached MAX_ITER
        // continue WHILE there is change in cluster assign and not reached MAX_ITER          
        } while (iters < constants::max_iter && !no_change);
    //    std::cerr << iters << " iterations\n";
    }

    void print_centroids(std::ostream& os) const {
        std::copy(centroids.begin(), centroids.end(), std::ostream_iterator<point<T> >(os, " "));
    }

    void print_assignment(std::ostream& os) const {
        std::copy(point2cluster.begin(), point2cluster.end(), std::ostream_iterator<int >(os, "\n"));
    }
    void print(std::ostream& os) const {
        std::copy(points.begin(), points.end(), std::ostream_iterator<point<T> >(os, " "));
        os << "\n";
    }
   
    void read(std::istream & is) {
        point<T> tmp;
        while (is >> tmp) {
            points.push_back(tmp);
        }
    }
};

template<typename T>
std::ostream & operator<<(std::ostream & os, const cloud<T> &obj) {
    obj.print(os);
    return os;
}

template<typename T>
std::istream  & operator>>(std::istream & is, cloud<T> &obj) {
    obj.read(is);
    return is;
}
}
#endif
