#ifndef VECTOR3_H
#define VECTOR3_H

namespace curiosity {

    template <typename T>
    class Vector3 {
    public:
        Vector3() { x = y = z = 0; }
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
        ~Vector3() {}

        inline T getX() const { return x; }
        inline void setX(int i) { x = i; }
        inline T getY() const { return y; }
        inline void setY(int i) { y = i; }
        inline T getZ() const { return z; }
        inline void setZ(int i) { z = i; }

        inline bool operator==(const Vector3<T> &other) const {
            if ((x == other.getX()) && (y == other.getY()) && (z == other.getZ()))
                return true;
            else
                return false;
        }
        inline bool operator!=(const Vector3<T> &other) const {
            return !(*this == other);
        }
        inline Vector3<T> operator+(const Vector3<T> &other) const {
            Vector3<T> res(x+other.x, y+other.y, z+other.z);
            return res;
        }
        inline Vector3<T> operator-(const Vector3<T> &other) const {
            Vector3<T> res(x-other.x, y-other.y, z-other.z);
            return res;
        }
        inline Vector3<T> operator*(T t) const {
            Vector3<T> res(t * x, t * y, t * z);
            return res;
        }
        inline T operator*(const Vector3<T> &other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        static inline Vector3<T> identity(int i) {
            Vector3<T> res;
            if (i == 1)
                res.setX(1);
            else if (i == 2)
                res.setY(1);
            else
                res.setZ(1);
            return res;
        }

        static inline Vector3<T> zero() {
            Vector3<T> res;
            return res;
        }

    private:
        T x;
        T y;
        T z;
    };

    template<typename T>
    inline Vector3<T> operator*(T t, const Vector3<T> &vec) {
        Vector3<T> res(t*vec.getX(), t*vec.getY(), t*vec.getZ());
        return res;
    }

    typedef Vector3<int> IntVector3;
    typedef Vector3<float> FloatVector3;
    typedef Vector3<double> DoubleVector3;

}

#endif // VECTOR3_H
