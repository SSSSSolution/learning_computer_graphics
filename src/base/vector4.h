#ifndef VECTOR4_H
#define VECTOR4_H

namespace curiosity {

    template <typename T>
    class Vector4 {
    public:
        Vector4() { x = y = z = w = 0; }
        Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        ~Vector4() {}

        inline T getX() const { return x; }
        inline void setX(int i) { x = i; }
        inline T getY() const { return y; }
        inline void setY(int i) { y = i; }
        inline T getZ() const { return z; }
        inline void setZ(int i) { z = i; }
        inline T getW() const { return w; }
        inline void setW(int i) { w = i; }

        inline bool operator==(const Vector4<T> &other) const {
            if ((x == other.getX()) && (y == other.getY()) &&
                    (z == other.getZ()) && (w == other.getW()))
                return true;
            else
                return false;
        }
        inline bool operator!=(const Vector4<T> &other) const {
            return !(*this == other);
        }
        inline Vector4<T> operator+(const Vector4<T> &other) const {
            Vector4<T> res(x+other.x, y+other.y, z+other.z, w+other.w);
            return res;
        }
        inline Vector4<T> operator-(const Vector4<T> &other) const {
            Vector4<T> res(x-other.x, y-other.y, z-other.z, w-other.w);
            return res;
        }
        inline Vector4<T> operator*(T t) const {
            Vector4<T> res(t * x, t * y, t * z, t * w);
            return res;
        }
        inline T operator*(const Vector4<T> &other) const {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        static inline Vector4<T> identity(int i) {
            Vector4<T> res;
            if (i == 1)
                res.setX(1);
            else if (i == 2)
                res.setY(1);
            else if (i == 3)
                res.setZ(1);
            else
                res.setW(1);
            return res;
        }

        static inline Vector4<T> zero() {
            Vector4<T> res;
            return res;
        }

    private:
        T x;
        T y;
        T z;
        T w;
    };

    template<typename T>
    inline Vector4<T> operator*(T t, const Vector4<T> &vec) {
        Vector4<T> res(t*vec.getX(), t*vec.getY(), t*vec.getZ(), t*vec.getW());
        return res;
    }

    typedef Vector4<int> IntVector4;
    typedef Vector4<float> FloatVector4;
    typedef Vector4<double> DoubleVector4;
}

#endif // VECTOR4_H
