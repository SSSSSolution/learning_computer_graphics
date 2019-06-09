#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "point3.h"
#include "vector3.h"
//#include "ray3.h"
//#include "sphere.h"
//#include "triangle3.h"
#include <QDebug>

#define PI (3.141592653)

namespace curiosity {
    template<typename T> class Sphere;
    template<typename T> class Ray3;
    template<typename T> class Triangle3;
    /*
     * 球体和射线的碰撞检测
     * 若有碰撞返回true和t0, t1
     *  碰撞点　p ＝　e + td;
     * 若无碰撞返回false
     */
    template<typename T>
    bool collisionDetection(Sphere<T> &sphere, Ray3<T> &ray3, T &t0, T &t1) {
        Point3<T> e = ray3.getE();
        Vector3<T> d = ray3.getDirection();
        Point3<T> c = sphere.getCenter();
        T r = sphere.getRadius();

        T discriminant = d * d * (e - c)*(e - c) - ((d * d)*(e - c)*(e - c)) + r * r;
        if (discriminant < 0)
            return false;
        // 需要修改
        t0 = ((T)-1 * d *(e - c) + std::sqrt(discriminant)) / (d * d);
        t1 = ((T)-1 * d *(e - c) - std::sqrt(discriminant)) / (d * d);
        return true;
    }
    /* 三角形和射线的碰撞检测 */
    template<typename T>
    bool collisionDetection(Triangle3<T> &tri, Ray3<T> &ray3, T &t) {
        T a, b, c, d, e, f, g, h, i, j, k, l;
        a = tri.getA().getX() - tri.getB().getX();
        b = tri.getA().getY() - tri.getB().getY();
        c = tri.getA().getZ() - tri.getB().getZ();
        d = tri.getA().getX() - tri.getC().getX();
        e = tri.getA().getY() - tri.getC().getY();
        f = tri.getA().getZ() - tri.getC().getZ();
        g = ray3.getDirection().getX();
        h = ray3.getDirection().getY();
        i = ray3.getDirection().getZ();
        j = tri.getA().getX() - ray3.getE().getX();
        k = tri.getA().getY() - ray3.getE().getY();
        l = tri.getA().getZ() - ray3.getE().getZ();

        T M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
        if (M == 0)
            return false;
        T gama = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
        if ((gama < 0) || (gama > 1))
            return false;
        T beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
        if ((beta < 0) || (beta+gama > 1))
            return false;

        t = -1*(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;
        if (t < 0)
            return false;
        return true;
    }
}
#endif // MATHUTIL_H
