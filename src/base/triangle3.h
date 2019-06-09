#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <point3.h>
#include "mathutil.h"

namespace curiosity {

    template <typename T>
    class Triangle3 {
    public:
        Triangle3() : a(Point3<T>::origin()),
                      b(Point3<T>::origin()),
                      c(Point3<T>::origin()) {}
        Triangle3(Point3<T> &a, Point3<T> &b, Point3<T> &c)
            : a(a), b(b), c(c) { }

        inline Point3<T> &getA() { return a; }
        inline void setA(Point3<T> &p) { a = p; }
        inline Point3<T> &getB() { return b; }
        inline void setB(Point3<T> &p) { b = p; }
        inline Point3<T> &getC() { return c; }
        inline void setC(Point3<T> &p) { c = p; }

//        inline T getArea() {
//            return 0.5 * (a.getX()*b.getY() + b.getX() * c.getY() + c.getX() * a.getY()
//                       - a.getX()*c.getY() + c.getX() * b.getY() + b.getX() * a.getY());
//        }

        /* 质心 */
//        inline Point3<T> getBrctr() const {

//        }
        inline bool intersection(Ray3<T> &ray, T &t) {
            return collisionDetection(*this, ray, t);
        }

    private:
        Point3<T> a;
        Point3<T> b;
        Point3<T> c;
    };

    typedef Triangle3<int> IntTriangle3;
    typedef Triangle3<float> FloatTriangle3;
    typedef Triangle3<double> DoubleTriangle3;
}
#endif // TRIANGLE_H
