#ifndef POINTS
#define POINTS

#include <iostream>
#include <limits>

namespace kmean {

template <typename T>
class point {
    T x, y, z;

    bool check_less_than_eps(T value) {
        T eps = std::numeric_limits<T>::epsilon();
        if (value < eps && value > -eps ) {
            return true;
        }
        return false;
    }
    public:

        point(T xc = 0.0, T yc = 0.0, T zc = 0.0): x(xc), y(yc), z(zc) {};

        T get_x() const { return x;}
        T get_y() const { return y;}
        T get_z() const { return z;}

        bool operator==(point<T> that) {
            bool a = check_less_than_eps(this->x - that.get_x()); 
            bool b = check_less_than_eps(this->y - that.get_y()); 
            bool c = check_less_than_eps(this->z - that.get_z()); 
            return a && b && c;
        }

       point & operator+= (const point<T> & that) {
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

template<typename T>
point<T> operator+(const point<T> & first, const point<T> & second) {
    point<T> res(first); // return value optimization, inside boost documentation boost::operator  but if you compile in c++11 it will use the move constructor
    return res += second;
}

template<typename T>
point<T> operator/(const point<T> & first, int denomenator) {
    point<T> res(first);
    return res /= denomenator;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const point<T> &obj ) {
    obj.print(os);
    return os;
}

template<typename T>
std::istream & operator>>(std::istream & is, point<T> & obj) {
    obj.read(is);
    return is;
}

}
#endif
