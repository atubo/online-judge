// https://www.luogu.org/problemnew/show/P2044
// [NOI2012]随机数生成器

#include <bits/stdc++.h>
using namespace std;

int64_t MOD;

// square matrix fast power
class Matrix {
public:
    __int128_t **m_;
    int n_;

public:
    Matrix(int n): n_(n) {
        alloc();
    }

    Matrix(const Matrix &other) {
        n_ = other.n_;
        alloc();
        for (int i = 0; i < n_; i++) {
            memcpy(m_[i], other.m_[i], n_ * sizeof(__int128_t));
        }
    }


    ~Matrix() {
        for (int i = 0; i < n_; i++) {
            delete[] m_[i];
        }
        delete[] m_;
    }

    static Matrix power(Matrix x, int64_t n) {
        Matrix ret(x.n_), tmp(x.n_);
        for (int i = 0; i < x.n_; i++) ret.m_[i][i] = 1;
        while (n) {
            if (n & 1) ret.mul(x, tmp);
            x.mul(x, tmp);
            n >>= 1;
        }
        return ret;
    }

    void print() const {
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < n_; j++) {
                printf("%ld ", (int64_t)m_[i][j]);
            }
            printf("\n");
        }
    }

private:
    void alloc() {
        m_ = new __int128_t*[n_]{};
        for (int i = 0; i < n_; i++) {
            m_[i] = new __int128_t[n_]{};
        }
    }

    void mul(const Matrix &rhs, Matrix &tmp) {
        for (int i = 0; i < n_; i++) {
            memset(tmp.m_[i], 0, n_ * sizeof(__int128_t));
            for (int k = 0; k < n_; k++) {
                if (!m_[i][k]) continue;
                for (int j = 0; j < n_; j++) {
                    tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j];
                    tmp.m_[i][j] %= MOD;
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
};
int64_t A, C, X0, N, G;

int main() {
    scanf("%ld%ld%ld%ld%ld%ld", &MOD, &A, &C, &X0, &N, &G);
    int64_t x1 = (__int128_t(A)*X0 + C) % MOD;
    Matrix m(3);
    m.m_[0][0] = A;
    m.m_[0][2] = C;
    m.m_[1][0] = 1;
    m.m_[2][2] = 1;
    auto mp = Matrix::power(m, N-1);
    int64_t xn = (mp.m_[0][0]*x1 + mp.m_[0][2]) % MOD;
    printf("%ld\n", xn % G);
    return 0;
}
