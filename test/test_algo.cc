#define BOOST_TEST_MODULE algo 
//#include <boost/test/included/unit_test.hpp>
//#include <boost/test/floating_point_comparison.hpp>
//#include "point.h"
//#include "algo.h"

#include "test_header.h"

BOOST_AUTO_TEST_CASE(dist) {
    float eps = 0.0001;
    kmean::point p1(1.4, -2.6, 3.78), p2(-5.8, 56.7, -9.1);
    float dist = kmean::dist_euclid(p1, p2);
    BOOST_CHECK_CLOSE(dist, 3734.2244, eps);

    kmean::point p3(1.4, -2.6, 3.78);
    dist = kmean::dist_euclid(p1, p3);
    BOOST_CHECK_CLOSE(dist, 0.0, eps);
}

BOOST_AUTO_TEST_CASE(closest) {
    kmean::point p1(1, 2, 3);
    kmean::point p2(11, 21, 31);
    std::vector<kmean::point> pv;
    for (int i = 0; i < 4; i++) {
        kmean::point tmp(i+10, i+20,i+30);
        pv.push_back(tmp);
    }
    int closest = find_closest_point(p1, pv);
    BOOST_CHECK_EQUAL(closest, 0);
    closest = find_closest_point(p2, pv);
    BOOST_CHECK_EQUAL(closest, 1);
}
