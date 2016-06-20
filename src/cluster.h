#include <iostream>
#include <random>
#include <vector>

#include "point.h"
#include "algo.h"
#include "misc.h"

#ifndef CLUSTER
#define CLUSTER
//to do namespace
namespace kmean {

class cloud {
    std::vector<point> points;
    std::vector<point> centroids;
    std::vector<point> old_centroids;
    // vector of values point i assigned to cluster k
    std::vector<int> point2cluster;
    std::vector<int> old_point2cluster;
    // number of clusters
    int cluster_num;

    void initialize() {
        // initialize a random generator
        // choose randomly k centroids
        random_generator rgen(0, points.size() - 1, cluster_num);
        // possible alternative 
        // std::copy(centroids.begin(),centroids.end(),points.begin()); 
        // std::shuffle(....) 
        // centroids.resize(clust_num); 
         
        for (int i = 0; i < cluster_num; ++i) {
            // check that they are unique!
            //implace_back maybe a solution 
            centroids.push_back(points[rgen()]);
        }

        old_centroids.resize(cluster_num);
        old_point2cluster.resize(points.size());
        std::cerr << "centroids.size = " << centroids.size() << std::endl;
    }

    void assign_clusters () {
        int psize = points.size();
        for (int i = 0; i < psize; ++i) {
            // find index of the centroid closest to the current point 
            point2cluster.push_back( find_closest_point(points[i], centroids)); 
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
        if (k_num > points.size()) {
            std::cerr << "Number of clusters should not be greater that cloud size.\n";
            exit(1);
        }
        cluster_num = k_num;
        int iters = 0;
        initialize();
        std::cerr << "initialize\n";
        do {
            old_centroids.assign(centroids.begin(), centroids.end());
            old_point2cluster.assign(point2cluster.begin(), point2cluster.end());
            // assign each point to a closest centroid
            assign_clusters();
            std::cerr << "assign_clusters\n";
            reassign_centroids();
            std::cerr << "reassign_centroids\n";
//            is_changed = check_assignment_changes();
        ++iters;
        // continue until no change in cluster values            
        } while (iters < 30);

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
