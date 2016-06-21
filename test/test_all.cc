#define BOOST_TEST_MODULE point 
//#include <boost/test/included/unit_test.hpp>
//#include <boost/test/floating_point_comparison.hpp>
//#include "point.h"
#include "test_header.h"

BOOST_AUTO_TEST_CASE(constructors)
{
    float eps = 0.0001;
    kmean::point obj_zero;
    BOOST_CHECK_CLOSE(obj_zero.get_x(), 0.0, eps);
    BOOST_CHECK_CLOSE(obj_zero.get_y(), 0.0, eps);
    BOOST_CHECK_CLOSE(obj_zero.get_z(), 0.0, eps);
    kmean::point obj(3.56, -7.56, 98);
    BOOST_CHECK_CLOSE(obj.get_x(), 3.56, eps);
    BOOST_CHECK_CLOSE(obj.get_y(), -7.56, eps);
    BOOST_CHECK_CLOSE(obj.get_z(), 98, eps);
}

BOOST_AUTO_TEST_CASE(equal)
{
    kmean::point a(3.56, 7.78, -9.98);
    kmean::point b(3.56, 7.78, -9.98);
    kmean::point c(-3.56, -7.78, -9.98);
    kmean::point d(-3.56, -7.78, -9.98000000000000000001);
    BOOST_CHECK(a == b);
    BOOST_CHECK(!(a == c));
    BOOST_CHECK(c == d);
}

BOOST_AUTO_TEST_CASE(arithmetic)
{
    //float eps = std::numeric_limits<float>::epsilon();
    float eps = 0.0001;
    kmean::point a(3.56, 7.78, -9.98);
    kmean::point b(5.56, -7.078, 19.8);
    kmean::point c(-3.56, -7.78, 9.98);
    kmean::point sum = a + c;
    BOOST_CHECK_CLOSE(sum.get_x(), 0.0, eps);
    BOOST_CHECK_CLOSE(sum.get_y(), 0.0, eps);
    BOOST_CHECK_CLOSE(sum.get_z(), 0.0, eps);
    sum += c;
    BOOST_CHECK_CLOSE(sum.get_x(), -3.56, eps);
    BOOST_CHECK_CLOSE(sum.get_y(), -7.78, eps);
    BOOST_CHECK_CLOSE(sum.get_z(), 9.98, eps);

    sum /= 2;
    BOOST_CHECK_CLOSE(sum.get_x(), -1.78, eps);
    BOOST_CHECK_CLOSE(sum.get_y(), -3.89, eps);
    BOOST_CHECK_CLOSE(sum.get_z(), 4.99, eps);
}

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
