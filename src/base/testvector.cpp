#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "vectorn.h"
#include "matrix.h"

#include <iostream>
using namespace std;
using namespace curiosity;

template<typename T>
void printVector2(const Vector2<T> &vec)
{
    cout << vec.getX() << "," << vec.getY() << endl;
}

template<typename T>
void printVector3(const Vector3<T> &vec)
{
    cout << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << endl;
}

template<typename T>
void printVector4(const Vector4<T> &vec)
{
    cout << vec.getX() << ", " << vec.getY() << ", "
         << vec.getZ() << ", " << vec.getW() << endl;
}

template<typename T>
void printVectorN(const VectorN<T> &vec)
{
    cout << "[";
    for (int i = 1; i <= vec.size(); ++i) {
        cout << vec.getN(i);
        if (i != vec.size())
            cout << ", ";
    }
    cout << "]";
    cout << endl;
}

template<typename T>
void printMatrix(const Matrix<T> &mat)
{
    std::vector<VectorN<T> > cols = mat.transpose().getColumns();
    typename std::vector<VectorN<T> >::const_iterator it;
    for (it = cols.begin(); it != cols.end(); ++it) {
        printVectorN(*it);
    }
}

int main()
{
    IntVector2 vec21(1,2);
    IntVector2 vec22(3,4);

    printVector2(vec21+vec22);
    printVector2(vec22-vec21);
    printVector2(vec21*5);
    printVector2(5*vec22);
    int res = vec21*vec22;
    cout << "res = " << res <<endl;

    IntVector3 vec31(1, 2, 3);
    IntVector3 vec32(4, 5, 6);

    printVector3(vec31+vec32); // 5, 7, 9
    printVector3(vec32-vec31); // 3, 3, 3
    printVector3(vec31*5);     // 5, 10, 15
    printVector3(5*vec32);     // 20, 25, 30
    res = vec32*vec31;         // 32
    cout << "res = " << res << endl;

    IntVector4 vec41(1, 2, 3, 4);
    IntVector4 vec42(5, 6, 7, 8);

    printVector4(vec41 + vec42); // 6, 8, 10, 12
    printVector4(vec42 - vec41); // 4, 4, 4, 4
    printVector4(vec41*5); // 5, 10, 15, 20
    printVector4(5*vec42); // 25, 30, 35, 40
    res = vec41 * vec42;           // 70
    cout << "res = " << res << endl;


    std::vector<float> vec1, vec2;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);

    FloatVectorN vectorn1(vec1);
    FloatVectorN vectorn2(vec2);
    printVectorN(vectorn1 + vectorn2);
    printVectorN(vectorn2 - vectorn1);
    printVectorN(vectorn1 * (float)5.1);
    printVectorN((float)5.1 * vectorn2);
    res = vectorn1 * vectorn2;
    cout << "res = " << res << endl;

    // test Matrix
    vector<FloatVectorN> cols;
    cols.push_back(vec1);
    cols.push_back(vec2);

    Matrix<float> mat1(cols);
    Matrix<float> mat2(cols);

    printMatrix(mat1+mat2);
    printMatrix(mat1-mat2);
    printMatrix(mat1 * (float)5.1);
    printMatrix((float)5.1 * mat1);

    printMatrix(Matrix<float>::identity(50));

    return 0;
}

















