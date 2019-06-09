#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QtTest>
#include <iostream>

#include "sphere.h"
#include "circle.h"
#include "ray3.h"

using namespace std;
using namespace curiosity;

class TestSphereCircle : public QObject
{
    Q_OBJECT
private slots:
    void testSphere();
    void testCircle();
    void testIntersection();
};
typedef double ele_type;
void TestSphereCircle::testSphere()
{
    Sphere<ele_type> sphere1;
    QVERIFY(sphere1 == sphere1);
    QVERIFY(sphere1.getCenter() == Point3<ele_type>::origin());
    QVERIFY(sphere1.getRadius() == 0);
    QVERIFY(sphere1.getArea() == 0);
    QVERIFY(sphere1.getVolume() == 0);

    Point3<ele_type> center(1, 1, 1);
    ele_type r = 365;
    Sphere<ele_type> sphere2(center, r);
    QVERIFY(sphere2.getCenter() == center);
    QVERIFY(sphere2.getRadius() == r);
    QVERIFY(sphere2.getArea() == 4*PI*r*r);
    QVERIFY(sphere2.getVolume() == 4.0*PI*r*r*r/3.0);
    QVERIFY(sphere1 != sphere2);
}

void TestSphereCircle::testCircle()
{
    Circle<ele_type> circle1;
    QVERIFY(circle1 == circle1);
    QVERIFY(circle1.getCenter() == Point2<ele_type>::origin());
    QVERIFY(circle1.getRadius() == 0);
    QVERIFY(circle1.getCircumference() == 0);
    QVERIFY(circle1.getArea() == 0);

    Point2<ele_type> center(1, 1);
    ele_type r = 10;
    Circle<ele_type> circle2(center ,r);
    QVERIFY(circle2.getCenter() == center);
    QVERIFY(circle2.getRadius() == r);
    QVERIFY(circle2.getArea() == PI*r*r);
    QVERIFY(circle2.getCircumference() == 2*PI*r);
    QVERIFY(circle2 != circle1);
}

void TestSphereCircle::testIntersection()
{
    Sphere<ele_type> sphere;
    sphere.setCenter(Point3<ele_type>::origin());
    sphere.setRadius(5.0);

    Ray3<ele_type> ray1;
    ray1.setE(Point3<ele_type>::origin());
    ray1.setDirection(Vector3<ele_type>::identity(6));

    ele_type t0 = 0, t1 = 0;
    qDebug() << sphere.intersection(ray1, t0, t1);
    qDebug() << t0 << " " << t1;
}
QTEST_MAIN(TestSphereCircle)
#include "test_sphere_circle.moc"
