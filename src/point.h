#include <iostream>
#include <limits>

#ifndef POINTS
#define POINTS

namespace kmean {

class point {
    float x, y, z;

    bool check_less_than_eps(float value) {
        float eps = std::numeric_limits<float>::epsilon();
        if (value < eps && value > -eps ) {
            return true;
        }
        return false;
    }
    public:

        point(float xc = 0.0, float yc = 0.0, float zc = 0.0): x(xc), y(yc), z(zc) {};

        float get_x() const { return x;}
        float get_y() const { return y;}
        float get_z() const { return z;}

        bool operator==(point that) {
            bool a = check_less_than_eps(this->x - that.get_x()); 
            bool b = check_less_than_eps(this->y - that.get_y()); 
            bool c = check_less_than_eps(this->z - that.get_z()); 
            return a && b && c;
        }

       point & operator+= (const point& that) {
            this->x += that.get_x();
            this->y += that.get_y();
            this->z += that.get_z();
            return *this;   
       }

       point & operator/= (int denom) {
            if (!denom) {
                std::cerr << "division by zero!\n";
                exit(1);
            }
            // x = x * 1/denom ; // reciprocal much faster but lower precision !
            this->x /= denom;
            this->y /= denom;
            this->z /= denom;
            return *this;   
       }
        void print(std::ostream & os) const {
           os << x << " " << y << " " << z << std::endl; 
        }

        void read(std::istream & is) {
            is >> x;
            is >> y;
            is >> z;
        }
};

point operator+(const point& first, const point& second) {
    point res(first); // return value optimization, inside boost documentation boost::operator  but if you compile in c++11 it will use the move constructor
    return res += second;
}

point operator/(const point& first, int denomenator) {
    point res(first);
    return res /= denomenator;
}
std::ostream & operator<<(std::ostream & os, const point &obj ) {
    obj.print(os);
    return os;
}

std::istream & operator>>(std::istream & is, point& obj) {
    obj.read(is);
    return is;
}

}
#endif
