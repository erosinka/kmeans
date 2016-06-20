#include <iostream>
#include <random>
#include <vector>
#include <cmath>

#include "point.h"
#include "algo.h"
#include "misc.h"

#ifndef CLUSTER
#define CLUSTER


namespace kmean {

class cloud {
    std::vector<point> points;
    std::vector<point> centroids;
    // vector of cluster id of each point i 
    std::vector<int> point2cluster;
    std::vector<int> old_point2cluster;
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

    void assign_clusters () {
        _cluster_assign_diff = 0;
        int psize = points.size();
        for (int i = 0; i < psize; ++i) {
            // find index of the centroid closest to the point i
            int new_cluster_id = find_closest_point(points[i], centroids);
            _cluster_assign_diff += ((point2cluster[i] == new_cluster_id) ? 0 : 1);
            point2cluster[i] = new_cluster_id;
        }
    }

    void reassign_centroids() {
        for (int i = 0; i < centroids.size(); ++i) {
            centroids[i] = find_cluster_center(points, point2cluster, i); 
        }
    }

    public:
        cloud() {
            centroids.reserve(4096);
            point2cluster.reserve(4096);
            points.reserve(4096);    
        }


    void clusterize(int k_num)  {
        if (!points.size()) {
            std::cerr << "Cloud is empty.\n";
            exit(1);
        }
        if (!k_num) {
            std::cerr << "Number of clusters should be non-zero.\n";
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
            // assign each point to a closest centroid
            assign_clusters();
            reassign_centroids();
            no_change = (_cluster_assign_diff < constants::EPS);
            ++iters;
        // continue UNTIL no change in cluster assign or reached MAX_ITER
        // continue WHILE there is change in cluster assign and not reached MAX_ITER          
        } while (iters < constants::MAX_ITER && !no_change);
        std::cerr << iters << " iterations\n";
    }

    void print_centroids(std::ostream& os) const {
        for (std::vector<point>::const_iterator it = centroids.begin(); it != centroids.end(); ++it) {
            os << *it;
        }
    }

    void print(std::ostream& os) const {
        for (std::vector<point>::const_iterator it = points.begin(); it != points.end(); ++it) {
            os << *it;
        }
        os << std::endl;
    }
    
    void read(std::istream & is) {
        point tmp;
        while (is >> tmp) {
            points.push_back(tmp);
        }
    }

    
};

std::ostream & operator<<(std::ostream & os, const cloud &obj) {
    obj.print(os);
    return os;
}

std::istream  & operator>>(std::istream & is, cloud &obj) {
    obj.read(is);
    return is;
}
}
#endif
