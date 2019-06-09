#ifndef POINT3_H
#define POINT3_H
#include "vector3.h"

namespace curiosity {

    template <typename T>
    class Point3 {
    public:
        Point3() : x(0), y(0), z(0) {}
        Point3(T x, T y, T z) : x(x), y(y), z(z) {}
//        Point3(const Point3 &p) {
//            x = p.x;
//            y = p.y;
//            z = p.z;
//        }
//        Point3 &operator=(const Point3 &other) {
//            x = other.x;
//            y = other.y;
//            z = other.z;
//        }
//        ~Point3() {}

        inline T& getX() { return x; }
        inline void setX(T value) { x = value; }
        inline T& getY() { return y; }
        inline void setY(T value) { y = value; }
        inline T& getZ() { return z; }
        inline void setZ(T value) { z = value; }

        inline bool operator==(const Point3<T> &other) const {
            if ( x == other.x && y == other.y && z == other.z)
                return true;
            else
                return false;
        }

        inline bool operator!=(const Point3<T> &other) const {
            return !(*this == other);
        }

        /* 两点相减得到向量　*/
        inline Vector3<T> operator-(const Point3<T> &other) const {
            Vector3<T> vec(x-other.x, y-other.y, z-other.z);
            return vec;
        }

        inline static Point3<T> origin() {
            Point3<T> o(0, 0, 0);
            return o;
        }

    private:
        T x;
        T y;
        T z;
    };

    typedef Point3<int> IntPoint3;
    typedef Point3<float> FloatPoint3;
    typedef Point3<double> DoublePoint3;
}
#endif // POINT3_H
