
#include <QtCore/QObject>
#include <QtCore/QDebug>

#include "vectorn.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix.h"
#include "point3.h"

#include <QtTest/QtTest>
#include <iostream>
using namespace std;
using namespace curiosity;

class TestVector : public QObject
{
    Q_OBJECT
private slots:
    void TestVector2();
    void TestVector3();
    void TestVector4();
    void TestVectorN();
    void TestMatrix();
    void TestPoint3();
};

typedef double ele_type;
void TestVector::TestVector2()
{
    Vector2<ele_type> int_vec1(1,0);
    Vector2<ele_type> int_vec2(0,1);
    QVERIFY(int_vec1 == int_vec1);
    QVERIFY(int_vec1 != int_vec2);

    Vector2<ele_type> int_vec3;
    Vector2<ele_type> int_vec4(0, 0);
    QVERIFY(int_vec3 == int_vec4);

    Vector2<ele_type> int_res;
    //　验证向量加法
    int_res = int_vec1 + int_vec2;
    QVERIFY(int_res == Vector2<ele_type>(1,1));
    //　验证向量减法
    int_res = int_vec1 - int_vec2;
    QVERIFY(int_res == Vector2<ele_type>(1,-1));
    //　验证向量内积
    ele_type r = int_vec1 * int_vec2;
    QVERIFY(r == 0);
    //　验证向量数乘
    int_res = (ele_type)10 * int_vec2;
    QVERIFY(int_res == Vector2<ele_type>(0,10));
    int_res = (ele_type)10 * int_vec2 * (ele_type)10;
    QVERIFY(int_res == Vector2<ele_type>(0,100));

    // identity
    QVERIFY(Vector2<ele_type>::identity(1) == Vector2<ele_type>(1, 0));
    QVERIFY(Vector2<ele_type>::identity(2) == Vector2<ele_type>(0, 1));

    // zero
    QVERIFY(Vector2<ele_type>::zero() == Vector2<ele_type>(0, 0));
}

void TestVector::TestVector3()
{
    Vector3<ele_type> vec1(1,2,3);
    Vector3<ele_type> vec2(4,5,6);
    QVERIFY(vec1 == vec1);
    QVERIFY(vec1 != vec2);

    Vector3<ele_type> vec3;
    Vector3<ele_type> vec4(0, 0, 0);
    QVERIFY(vec3 == vec4);

    Vector3<ele_type> int_res;
    //　验证向量加法
    int_res = vec1 + vec2;
    QVERIFY(int_res == Vector3<ele_type>(5, 7, 9));
    //　验证向量减法
    int_res = vec1 - vec2;
    QVERIFY(int_res == Vector3<ele_type>(-3, -3, -3));
    //　验证向量内积
    ele_type r = vec1 * vec2;
    QVERIFY(r == 32);
    //　验证向量数乘
    int_res = (ele_type)10 * vec2;
    QVERIFY(int_res == Vector3<ele_type>(40, 50, 60));
    int_res = (ele_type)10 * vec2 * (ele_type)10;
    QVERIFY(int_res == Vector3<ele_type>(400, 500, 600));

    // identity
    QVERIFY(Vector3<ele_type>::identity(1) == Vector3<ele_type>(1, 0, 0));
    QVERIFY(Vector3<ele_type>::identity(2) == Vector3<ele_type>(0, 1, 0));
    QVERIFY(Vector3<ele_type>::identity(3) == Vector3<ele_type>(0, 0, 1));

    // zero
    QVERIFY(Vector3<ele_type>::zero() == Vector3<ele_type>(0, 0, 0));
}

void TestVector::TestVector4()
{
    Vector4<ele_type> vec1(1, -2, 3, -4);
    Vector4<ele_type> vec2(-5, 6, -7, 8);
    QVERIFY(vec1 == vec1);
    QVERIFY(vec1 != vec2);

    Vector4<ele_type> vec3;
    Vector4<ele_type> vec4(0, 0, 0, 0);
    QVERIFY(vec3 == vec4);

    Vector4<ele_type> vec_res;
    //　验证向量加法
    vec_res = vec1 + vec2;
    QVERIFY(vec_res == Vector4<ele_type>(-4, 4, -4, 4));
    //　验证向量减法
    vec_res = vec1 - vec2;
    QVERIFY(vec_res == Vector4<ele_type>(6, -8, 10, -12));
    //　验证向量内积
    ele_type r = vec1 * vec2;
    QVERIFY(r == -70);
    //　验证向量数乘
    vec_res = (ele_type)10 * vec2;
    QVERIFY(vec_res == Vector4<ele_type>(-50, 60, -70, 80));
    vec_res = (ele_type)10 * vec2 * (ele_type)10;
    QVERIFY(vec_res == Vector4<ele_type>(-500, 600, -700, 800));

    // identity
    QVERIFY(Vector4<ele_type>::identity(1) == Vector4<ele_type>(1, 0, 0, 0));
    QVERIFY(Vector4<ele_type>::identity(2) == Vector4<ele_type>(0, 1, 0, 0));
    QVERIFY(Vector4<ele_type>::identity(3) == Vector4<ele_type>(0, 0, 1, 0));
    QVERIFY(Vector4<ele_type>::identity(4) == Vector4<ele_type>(0, 0, 0, 1));

    // zero
    QVERIFY(Vector4<ele_type>::zero() == Vector4<ele_type>(0, 0, 0, 0));
}

void TestVector::TestVectorN()
{
    VectorN<ele_type> vec1(5);
    vector<ele_type> tmp1;
    for (int i = 0; i < 5; ++i) {
        tmp1.push_back(i);
    }
    vector<ele_type> tmp2;
    for (int i = 0; i < 5; ++i) {
        tmp2.push_back(i+5);
    }
    VectorN<ele_type> vec2(tmp1); // 0, 1, 2, 3, 4
    VectorN<ele_type> vec3(tmp2); // 5, 6, 7, 8, 9
    QVERIFY(vec1 == vec1);
    QVERIFY(vec2 != vec3);
    QVERIFY(vec1.size() == 5);
    QVERIFY(vec2.size() == 5);
    QVERIFY(vec3.size() == 5);

    for (int i = 1; i <= 5; ++i)
    {
        QVERIFY(vec1.getN(i) == 0);
        QVERIFY(vec2.getN(i) == i-1);
        QVERIFY(vec3.getN(i) == i+4);
    }

    VectorN<ele_type> vec4(10);
    for (int i = 0; i < 10; ++i)
        vec4.setN(i+1, i); // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    for (int i = 0; i < 10; ++i)
        QVERIFY(vec4.getN(i+1) == i);


    tmp1.clear();
    tmp1.push_back(5);
    tmp1.push_back(7);
    tmp1.push_back(9);
    tmp1.push_back(11);
    tmp1.push_back(13);
    VectorN<ele_type> vec_res1(tmp1);
    QVERIFY(vec_res1 == vec2 + vec3);

    tmp1.clear();
    tmp1.push_back(5);
    tmp1.push_back(5);
    tmp1.push_back(5);
    tmp1.push_back(5);
    tmp1.push_back(5);
    VectorN<ele_type> vec_res2(tmp1);
    QVERIFY(vec_res2 == vec3-vec2);

    // 数乘
    tmp1.clear();
    tmp1.push_back(0);
    tmp1.push_back(5);
    tmp1.push_back(10);
    tmp1.push_back(15);
    tmp1.push_back(20);
    VectorN<ele_type> vec_res3(tmp1);
    QVERIFY((ele_type)5*vec2 == vec_res3);
    QVERIFY(vec2*(ele_type)5 == vec_res3);

    // 内积
    ele_type res = 80;
    QVERIFY(vec2*vec3 == res);
    QVERIFY(vec3*vec2 == res);

    vec3 = vec2;
    QVERIFY(vec3 == vec2);
}

template<typename T>
static void printMatrix(const Matrix<T> &mat)
{
    for (size_t j = 1; j <= mat.row(); ++j) {
        for (size_t i = 1; i <= mat.col(); ++i) {
            cout << mat.getValue(j, i) << " ";
        }
        cout << endl;
    }
}

void TestVector::TestMatrix()
{
    Matrix<ele_type> mat2(3,2);
    printMatrix(mat2);

    VectorN<ele_type> vec1(3);
    VectorN<ele_type> vec2(3);
    std::vector<VectorN<ele_type> > cols;
    cols.push_back(vec1);
    cols.push_back(vec2);
    Matrix<ele_type> mat3(cols);
    QVERIFY(mat2 == mat3);
    int k = 0;
    for (size_t i = 1; i <= 3; ++i) {
        for (size_t j = 1; j <= 2; ++j) {
            mat3.setValue(i, j, k++);
        }
    }
    /*mat2   mat3
     * 2 3   1 2
     * 3 4   3 4
     * 4 5   5 6
     */
    printMatrix(mat2);

    QVERIFY(mat2.row() == 3);
    QVERIFY(mat2.col() == 2);

    // setValue
    for (size_t i = 1; i <= 3; ++i) {
        for (size_t j = 1; j <= 2; ++j) {
            mat2.setValue(i, j, i+j);
        }
    }
    cout << endl;
    printMatrix(mat2);
    // ==
    cout << "==" << endl;
    QVERIFY(mat2 == mat2);
    cout << "!=" << endl;
    QVERIFY(mat2 != mat3);

    // +
    printMatrix(mat3);
    cout << "+" << endl;
    printMatrix(mat2 + mat3);
    // -
    cout << "-" << endl;
    printMatrix(mat2 - mat3);
    // 数乘
    cout << "here" << mat3.getColumns().at(1).size() << endl;
    printMatrix((ele_type)5 * mat3);
    printMatrix(mat3 * (ele_type)5);
    // *
    printMatrix(mat3);
    printMatrix(mat2.transpose());
    printMatrix(mat3 * mat2.transpose());
    printMatrix(mat2 * mat3.transpose());

    cout << "*********transpose***********" << endl;
    mat2.transpose();
    cout << "*********transpose***********" << endl;

    Matrix<ele_type> mat4(3,2);
    mat4 = mat3;
    printMatrix(mat4);
    printMatrix(mat3);

    printMatrix(Matrix<ele_type>::identity(10));
    printMatrix(Matrix<ele_type>::zero(10, 10));
}

void TestVector::TestPoint3()
{
    Point3<ele_type> p1;
    Point3<ele_type> p2(1,2,3);
    QVERIFY(p1 == p1);
    QVERIFY(p1 != p2);
    QVERIFY(p1 == Point3<ele_type>::origin());

    Point3<ele_type> p3 = p2;
    p1 = p2;

    Vector3<ele_type> vec = p3 -p2;
    QVERIFY(vec == Vector3<ele_type>::zero());
}
QTEST_MAIN(TestVector)
#include "test_vector.moc"












