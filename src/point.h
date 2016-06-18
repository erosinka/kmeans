#include <iostream>
#ifndef POINTS
#define POINTS

namespace kmean {

class point {
    float x, y, z;

    public:

        point(float xc = 0.0, float yc = 0.0, float zc = 0.0): x(xc), y(yc), z(zc) {};

        float get_x() { return x;}
        float get_y() { return y;}
        float get_z() { return z;}

        bool operator==(point that) {
            if (this->x != that.get_x())
                return false;
            if (this->y != that.get_y())
                return false;
            if (this->z != that.get_z())
                return false;
            return true;
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
