#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "vectorn.h"
#include "stdexcept"

namespace curiosity {

    template<typename T>
    class Matrix {
    public:
        Matrix() {
        }

        Matrix(int r, int c) {
            for (int i = 0; i < c; i++) {
                columns.push_back(VectorN<T>::zero(r));
            }
        }

        Matrix(std::vector<VectorN<T> > &cols) {
            if (cols.size() == 0)
                throw std::runtime_error("matrix: cols is 0");
            size_t rows = cols.at(0).size();
            if (rows == 0)
                throw std::runtime_error("matrix: rows is 0");
            typename std::vector<VectorN<T> >::const_iterator it;
            for (it = cols.begin(); it != cols.end(); ++it) {
                columns.push_back(*it);
                if ((*it).size() != rows)
                    throw std::runtime_error("matrix: rows is not same");
            }
        }

        ~Matrix() {}

        /* 矩阵行数　*/
        inline size_t row() const {
            return columns.at(0).size();
        }

        /*　矩阵列数　*/
        inline size_t col() const {
            return columns.size();
        }

        /* 返回r行n列的值 */
        inline T getValue(int r, int c) const {
            return columns.at(c-1).getN(r);
        }

        /* 设置r行ｎ列的值 */
        inline void setValue(int r, int c, T value) {
            columns.at(c-1).setN(r, value);
        }

        inline const std::vector<VectorN<T> >& getColumns() const {
            return columns;
        }

        bool operator==(const Matrix<T> &other) const {
            if ((row() != other.row()) || (col() != other.col()))
                return false;
            typename std::vector<VectorN<T> >::const_iterator it1, it2;
            for (it1 = columns.begin(), it2 = other.columns.begin();
                 it1 != columns.end(); ++it1, ++it2) {
                if (*it1 != *it2)
                    return false;
            }
            return true;
        }

        bool operator!=(const Matrix<T> &other) const
        {
            return !(*this == other);
        }

        /* 矩阵加法 */
        Matrix<T> operator+(const Matrix<T> &other) const {
            if ((row() != other.row()) || (col() != other.col()))
                throw std::runtime_error("matrix +: sizes are not same");
            std::vector<VectorN<T> > new_columns;
            typename std::vector<VectorN<T> >::const_iterator it;
            int i = 0;
            for (it = columns.begin(); it != columns.end(); ++it) {
                VectorN<T> new_col(*it + other.columns.at(i++));
                new_columns.push_back(new_col);
            }
            Matrix<T> matrix(new_columns);
            return matrix;
        }

        /* 矩阵减法 */
        Matrix<T> operator-(const Matrix<T> &other) const {
            if ((row() != other.row()) || (col() != other.col()))
                throw std::runtime_error("matrix +: sizes are not same");
            std::vector<VectorN<T> > new_columns;
            typename std::vector<VectorN<T> >::const_iterator it;
            int i = 0;
            for (it = columns.begin(); it != columns.end(); ++it) {
                VectorN<T> new_col(*it - other.columns.at(i++));
                new_columns.push_back(new_col);
            }
            Matrix<T> matrix(new_columns);
            return matrix;
        }

        /* 矩阵数乘 */
        Matrix<T> operator*(T t) const {
            std::vector<VectorN<T> > new_columns;
            typename std::vector<VectorN<T> >::const_iterator it;
            for (it = columns.begin(); it != columns.end(); ++it) {
                VectorN<T> new_col(*it * t);
                new_columns.push_back(new_col);
            }
            Matrix<T> matrix(new_columns);
            return matrix;
        }

        /* 矩阵乘法 */
        inline Matrix<T> operator*(const Matrix<T> &other) const {
            if (col() != other.row())
                throw std::runtime_error("matrix *: size error");
            std::vector<VectorN<T> > new_cols;
            typename std::vector<VectorN<T> >::const_iterator it;
            for (it = other.columns.begin(); it != other.columns.end(); ++it) {
                VectorN<T> tmp(row());
                for (size_t i = 1; i <= (*it).size(); ++i) {
                    tmp = tmp + columns.at(i-1) * (*it).getN(i);
                }
                new_cols.push_back(tmp);
            }
            Matrix<T> mat(new_cols);
            return mat;
        }

        /* 矩阵转置 */
        Matrix<T> transpose() const {
            std::vector<VectorN<T> > new_columns;
            for (size_t i = 1; i <= row(); ++i) {
                std::vector<T> tmp;
                typename std::vector<VectorN<T> >::const_iterator it;
                for (it = columns.begin(); it != columns.end(); ++it) {
                    tmp.push_back((*it).getN(i));
                }
                VectorN<T> new_col(tmp);
                new_columns.push_back(new_col);
            }
            Matrix<T> mat(new_columns);
            return mat;
        }

        /* 返回n阶单位阵 */
        static Matrix<T> identity(int n) {
            std::vector<VectorN<T> > columns;
            for (int i = 0; i < n; i++) {
                columns.push_back(VectorN<T>::identity(n, i+1));
            }
            Matrix<T> matrix(columns);
            return matrix;
        }

        /* 返回r行c列的零矩阵 */
        static Matrix<T> zero(int r, int c) {
            Matrix<T> mat(r, c);
            return mat;
        }

        template<typename Q>
        friend Matrix<Q> operator*(Q t , const Matrix<Q>& mat);

    private:
        std::vector<VectorN<T> > columns;
    };

    /* 矩阵数乘 */
    template<typename T>
    Matrix<T> operator*(T t , const Matrix<T>& mat) {
        std::vector<VectorN<T> > new_columns;
        typename std::vector<VectorN<T> >::const_iterator it;
        for (it = mat.columns.begin(); it != mat.columns.end(); ++it) {
            VectorN<T> new_col((*it) * t);
            new_columns.push_back(new_col);
        }
        Matrix<T> matrix(new_columns);
        return matrix;
    }
}

#endif // MATRIX_H
