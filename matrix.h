//
// Created by admin on 03.11.2020.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <vector>
#include <numeric>
#include <typeinfo>

int gcd(int a, int b) {
    for (;;) {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b) {
    int temp = gcd(a, b);
    if (temp == 0) { return 0; }
    return temp ? (a / temp * b) : 0;
}

template<typename T>
class Matrix {
private:
    T **matrix;
    int n;
public:
    Matrix(int number) {
        matrix = new T *[number];
        for (int i = 0; i < number; ++i) {
            matrix[i] = new T[number];
        }
        n = number;
    }

    Matrix(int number, int par) {
        matrix = new T *[number];
        for (int i = 0; i < number; ++i) {
            matrix[i] = new T[number];
        }
        n = number;
        n = number;
        if (par == 0) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (par == 1) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j)
                        matrix[i][j] = 1;
                }
            }
        }
    }

    Matrix(T **inc_matrix, int inc_n) {
        matrix = inc_matrix;
        n = inc_n;
    }

    Matrix(const Matrix &m) {
        matrix = new T *[m.n];
        for (int i = 0; i < m.n; ++i) {
            matrix[i] = new T[m.n];
        }
        n = m.n;
        for (int i = 0; i < m.n; ++i) {
            for (int j = 0; j < m.n; ++j) {
                matrix[i][j] = m.matrix[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < n; i++)
            delete[] matrix[i];

        delete[] matrix;
    }

    struct Row {
        T *row;
        int n;

        T &operator[](int i) { return row[i]; }
    };

    void swap_rows(Matrix &inc_matrix, int i, int j) {
        for (int k = i ; k < n; ++k) {
            T tmp = inc_matrix.matrix[i][k];
            inc_matrix.matrix[i][k] = inc_matrix.matrix[j][k];
            inc_matrix.matrix[j][k] = tmp;
        }
    }


    float determinant() {
        Matrix<T> backup(*this);
        T divider = static_cast<T>(1);
        T determinant;
        for (int k = 0; k < n - 1; ++k) {
            if (backup.matrix[k][k] == 0) {
                for (int l = k + 1; l < n; ++l) {
                    if (backup.matrix[l][k] == 0) {
                        if (l == n - 1)
                            return 0;
                        continue;
                    } else {
                        swap_rows(backup, k, l);
                        if ((l - k) % 2 == 1)
                            divider *= -1;
                        k--;
                        break;
                    }
                }
            } else {
                for (int i = k + 1; i < n; ++i) {
                    T tmp1 = lcm(backup.matrix[k][k], backup.matrix[i][k]);
                    T tmp2 = backup.matrix[i][k];
                    T tmp3 = backup.matrix[k][k];
                    if (backup.matrix[i][k] == 0)
                        continue;
                    for (int j = k; j < n; ++j) {
                        backup.matrix[k][j] *= (tmp1 / tmp3);
                        backup.matrix[i][j] *= (tmp1 / tmp2);
                        backup.matrix[i][j] -= backup.matrix[k][j];
                    }

                    divider *= (tmp1 / tmp2);
                    backup.matrix[k][k] /= (tmp1 / tmp3);
                }
            }
        }
        T composition = backup.matrix[0][0];
        for (int i = 1; i < n; ++i) {
            composition *= backup.matrix[i][i];
        }

        determinant = composition / divider;
        return determinant;
    }

    int get_n() {
        return n;
    }

    Row operator[](int i) {
        return Row{matrix[i]};
    }


};

template<typename T>
std::istream &operator>>(std::istream &is, Matrix<T> &m) {
    for (int i = 0; i < m.get_n(); ++i) {
        for (int j = 0; j < m.get_n(); ++j) {
            int temp;
            is >> temp;
            m[i][j] = temp;
        }
    }
    return is;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, Matrix<T> &m) {
    os << "\n";
    for (int i = 0; i < m.get_n(); ++i) {
        for (int j = 0; j < m.get_n(); ++j) {
            os << m[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

#endif //MATRIX_MATRIX_H
