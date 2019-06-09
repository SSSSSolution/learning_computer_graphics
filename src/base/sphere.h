#ifndef SPHERE_H
#define SPHERE_H
#include <stdexcept>
#include "point3.h"
#include "mathutil.h"
//#include "ray3.h"


namespace curiosity {
    template < typename T>
    class Sphere {
    public:
        Sphere() : center(Point3<T>::origin()), radius(0) {}
        Sphere(Point3<T>& c, T r) : center(c), radius(r) {
            if (r < 0)
                throw std::runtime_error("Sphere:: radium < 0!");
        }

        inline Point3<T> getCenter() { return center; }
        inline void setCenter(const Point3<T> &p) { center = p; }
        inline T getRadius() { return radius; }
        inline void setRadius(T r) {
            if (r < 0)
                throw std::runtime_error("Shpere:: radium < 0!");
            radius = r;
        }

        inline bool operator==(const Sphere<T>& other) const {
            if (center == other.center && radius == other.radius)
                return true;
            else
                return false;
        }

        inline bool operator!=(const Sphere<T> &other) const {
            return !(*this == other);
        }

        inline T getArea() {
            return 4.0 * PI * radius * radius;
        }

        inline T getVolume() {
            return 4.0 * PI * radius * radius * radius / 3.0;
        }

        /* 碰撞检测 */
        inline bool intersection(Ray3<T> &ray3, T &t0, T &t1) {
            return collisionDetection(*this, ray3, t0, t1);
        }

    private:
        Point3<T> center;
        T radius;
    };

    typedef Sphere<float> FloatSphere;
    typedef Sphere<double> DoubleSphere;
}
#endif // SPHERE_H
