#ifndef CIRCLE_H
#define CIRCLE_H
#include <stdexcept>
#include "point2.h"
#include "mathutil.h"

namespace curiosity {

    template<typename T>
    class Circle {
    public:
        Circle() : center(Point2<T>::origin()), radius(0) {}
        Circle(Point2<T> &c, T r) : center(c), radius(r) {
            if (radius < 0)
                std::runtime_error("Circle::radius < 0!");
        }

        inline Point2<T> getCenter() { return center; }
        inline void setCenter(Point2<T> &p) { center = p; }
        inline T getRadius() { return radius; }
        inline void setRadius(T r) {
            if (radius < 0)
                std::runtime_error("Circle:: radius < 0!");
            radius = r;
        }

        inline bool operator==(Circle<T> &other) {
            if (center == other.center && radius == other.radius)
                return true;
            return false;
        }

        inline bool operator!=(Circle<T> &other) {
            return !(*this == other);
        }

        inline T getCircumference() {
            return 2*PI*radius;
        }

        inline T getArea() {
            return PI*radius*radius;
        }

    private:
        Point2<T> center;
        T radius;
    };

    typedef Circle<float> FloatCircle;
    typedef Circle<double> DoubleCircle;
}
#endif // CIRCLE_H
