#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QtTest>
#include <iostream>

#include "ray3.h"
#include "point3.h"
#include "vector3.h"
#include "sphere.h"
#include "triangle3.h"

using namespace std;
using namespace curiosity;

class TestRay : public QObject
{
    Q_OBJECT
private slots:
    void TestRay3();
    void benchMark();
};

typedef double ele_type;
void TestRay::TestRay3()
{
    Ray3<ele_type> ray1, ray2;
    QVERIFY(ray1.getE() == Point3<ele_type>::origin());
    QVERIFY(ray1.getDirection() == Vector3<ele_type>::zero());

    Point3<ele_type> p(1,0, 0);
    ray2.setE(p);
    Vector3<ele_type> v(1,0,0);
    ray2.setDirection(v);

    Sphere<ele_type> sphere;
    Point3<ele_type> center(10, 0, 0);
    sphere.setCenter(center);
    ele_type r = 1;
    sphere.setRadius(r);
    ele_type t0 = 0, t1 = 0;
    qDebug() << ray2.intersection(sphere, t0, t1);
    qDebug() << t0 << " " << t1;

    Triangle3<ele_type> triangle;
    Point3<ele_type> a(2,  0,  1);
    Point3<ele_type> b(2,  1, -1);
    Point3<ele_type> c(2, -1, -1);
    triangle.setA(a);
    triangle.setB(b);
    triangle.setC(c);
    ele_type t;
    ray2.intersection(triangle, t);
    qDebug() << t;
}

void TestRay::benchMark()
{
    Ray3<ele_type> ray1, ray2;
    Point3<ele_type> p(1,0, 0);
    ray2.setE(p);
    Vector3<ele_type> v(1,0,0);
    ray2.setDirection(v);

    Triangle3<ele_type> triangle;
    Point3<ele_type> a(100,  -19,  100);
    Point3<ele_type> b(223,  123, -100);
    Point3<ele_type> c(212, -123, -123);
    triangle.setA(a);
    triangle.setB(b);
    triangle.setC(c);
    ele_type t;
    QBENCHMARK {
        ray2.intersection(triangle, t);
    }
    qDebug() << t;
}

QTEST_MAIN(TestRay)
#include "test_ray.moc"
