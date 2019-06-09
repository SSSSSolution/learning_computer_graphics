#ifndef RAY3_H
#define RAY3_H

#include "point3.h"
#include "vector3.h"
#include "mathutil.h"

namespace curiosity {
    template <typename T>
    class Ray3 {
    public:
        Ray3() {
            e = Point3<T>::origin();
            direction = Vector3<T>::zero();
        }
        Ray3(Point3<T> &p, Vector3<T> &v) : e(p), direction(v) {}

        inline Point3<T>& getE() { return e; }
        inline void setE(const Point3<T> &p) { e = p; }
        inline Vector3<T>& getDirection() { return direction; }
        inline void setDirection(const Vector3<T> &v) { direction = v; }

        inline bool intersection(Sphere<T> &sphere, T &t0, T &t1) {
            return collisionDetection(sphere, *this, t0, t1);
        }

        inline bool intersection(Triangle3<T> &triganle, T &t) {
            return collisionDetection(triganle, *this, t);
        }

    private:
        Point3<T> e;
        Vector3<T> direction;
    };
}
#endif // RAY3_H
