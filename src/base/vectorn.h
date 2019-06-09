#ifndef VECTORN_H
#define VECTORN_H

#include <vector>
#include <stdexcept>

namespace curiosity {

    template <typename T>
    class VectorN {
    public:
        VectorN(int n) {
            if (n <= 0)
                throw std::runtime_error("VectorN: size can't less than 1");
            for (int i = 0; i < n; ++i) {
                vec.push_back(0);
            }
        }

        VectorN(const std::vector<T> &v) { vec = v; }

        ~VectorN() {}

        inline size_t size() const { return vec.size(); }

        inline T getN(size_t index) const {
            if ((index <= 0) || (index > vec.size()))
                throw std::runtime_error("VectorN::getN: out of range");
            return vec.at(index-1);
        }

        inline void setN(size_t index, T value) {
            if ((index <= 0) || (index >vec.size()))
                throw std::runtime_error("VectorN::setN: out of range");
            vec[index-1] = value;
        }

        bool operator==(const VectorN<T> &other) const {
            if (size() != other.size())
                return false;
            typename std::vector<T>::const_iterator it1, it2;
            for (it1 = vec.begin(), it2 = other.vec.begin(); it1 != vec.end(); ++it1, ++it2) {
                if (*it1 != *it2)
                    return false;
            }
            return true;
        }

        bool operator!=(const VectorN<T> &other) const {
            return !(*this == other);
        }

        VectorN<T> operator+(const VectorN<T> &other) const {
            if (vec.size() != other.size())
                throw std::runtime_error("VectorN +: two vectors' length are not same.");
            std::vector<T> new_vec;
            int i = 1;
            for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
                new_vec.push_back(*it + other.getN(i++));
            }
            VectorN<T> res(new_vec);
            return res;
        }

        VectorN<T> operator-(const VectorN<T> &other) const {
            if (vec.size() != other.size())
                throw std::runtime_error("VectorN -: two vectors' length are not same.");
            std::vector<T> new_vec;
            int i = 1;
            for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
                new_vec.push_back(*it - other.getN(i++));
            }
            VectorN<T> res(new_vec);
            return res;
        }

        VectorN<T> operator *(T t) const {
            std::vector<T> new_vec;
            for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
               new_vec.push_back(*it * t);
            }
            VectorN<T> res(new_vec);
            return res;
        }

        T operator*(const VectorN<T> &other) const {
            if (vec.size() != other.size())
                throw std::runtime_error("VectorN *: two vectors' lenght are not same");
            T res = *(vec.begin()) * other.getN(1);
            int i = 2;
            for (typename std::vector<T>::const_iterator it = vec.begin() + 1; it != vec.end(); ++it) {
                res += *it * other.getN(i++);
            }
            return res;
        }

        static inline VectorN<T> identity(int n, int i) {
            VectorN<T> res(n);
            res.setN(i, 1);
            return res;
        }

        static inline VectorN<T> zero(int n) {
            VectorN<T> res(n);
            return res;
        }

    private:
        std::vector<T> vec;
    };

    template<typename T>
    inline VectorN<T> operator*(T t, const VectorN<T> &vn) {
        std::vector<T> new_vec;
        for (size_t i = 1; i <= vn.size(); i++) {
            new_vec.push_back(t * vn.getN(i));
        }
        VectorN<T> res(new_vec);
        return res;
    }

    typedef VectorN<int> IntVectorN;
    typedef VectorN<float> FloatVectorN;
    typedef VectorN<double> DoubleVectorN;

}
#endif // VECTORN_H
