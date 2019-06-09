#ifndef VECTOR2_H
#define VECTOR2_H

namespace curiosity {

	template <typename T>
	class Vector2 {
	public:
        Vector2() { x = y = 0; }
        Vector2(T x, T y) : x(x), y(y) {}
        ~Vector2() {}

        inline T getX() const { return x; }
        inline void setX(int i) { x = i; }
        inline T getY() const { return y; }
        inline void setY(int i) { y = i; }

        inline bool operator==(const Vector2<T> &other) const {
            if ((x == other.getX()) && (y == other.getY()))
                return true;
            else
                return false;
        }
        inline bool operator!=(const Vector2<T> &other) const {
            return !(*this == other);
        }
        inline Vector2<T> operator+(const Vector2<T> &other) const {
            Vector2<T> res(x+other.x, y+other.y);
            return res;
        }
        inline Vector2<T> operator-(const Vector2<T> &other) const {
            Vector2<T> res(x-other.x, y-other.y);
            return res;
        }
        inline Vector2<T> operator*(T t) const {
            Vector2<T> res(t * x, t * y);
            return res;
        }
        inline T operator*(const Vector2<T> &other) const {
            return x * other.x + y * other.y;
        }

        static inline Vector2<T> identity(int i) {
            Vector2<T> res;
            if (i == 1)
                res.setX(1);
            else
                res.setY(1);
            return res;
        }

        static inline Vector2<T> zero() {
            Vector2<T> res;
            return res;
        }

	private:
		T x;
		T y;
    };

    template<typename T>
    inline Vector2<T> operator*(T t, const Vector2<T> &vec) {
        Vector2<T> res(t*vec.getX(), t*vec.getY());
        return res;
    }

    typedef Vector2<int> IntVector2;
    typedef Vector2<float> FloatVector2;
    typedef Vector2<double> DoubleVector2;

}
#endif
