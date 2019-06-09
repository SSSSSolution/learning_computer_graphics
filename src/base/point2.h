#ifndef POINT2_H
#define POINT2_H
#include "vector2.h"

namespace curiosity {

    template<typename T>
    class Point2 {
    public:
        Point2() : x(0), y(0) {}
        Point2(T x, T y) : x(x), y(y) {}

        inline T& getX() { return x; }
        inline void setX(T value) { x = value; }
        inline T& getY() { return y; }
        inline void setY(T value) { y = value; }

        inline bool operator==(const Point2<T> &other) const {
            if (x == other.x && y == other.y)
                return true;
            return false;
        }

        inline bool operator!=(const Point2<T> &other) const {
            return !(*this == other);
        }

        /* 两点相减得到向量　*/
        inline Vector2<T> operator-(const Point2<T> &other) const {
            Vector2<T> vec(x - other.x, y - other.y);
            return vec;
        }

        inline static Point2<T> origin() {
            Point2<T> o(0, 0);
            return o;
        }

    private:
        T x;
        T y;
    };

    typedef Point2<int> IntPoint2;
    typedef Point2<float> FloatPoint2;
    typedef Point2<double> DoublePoint2;
}
#endif // POINT2_H
