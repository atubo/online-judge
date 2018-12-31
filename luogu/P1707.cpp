// https://www.luogu.org/problemnew/show/P1707
// 刷题比赛

#include <bits/stdc++.h>
using namespace std;

int64_t K;

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

    void set(int r, int c, int v) {
        m_[r][c] = v;
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
                    (tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j]) %= K;
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
};

int64_t N;
int P, Q, R, T;
int U, V, W;
int X, Y, Z;

int64_t tally(const Matrix &m, int r) {
    __int128_t ans = (m.m_[r][0] + m.m_[r][1] + m.m_[r][2]) * 3
        + (m.m_[r][3] + m.m_[r][4] + m.m_[r][5])
        + (m.m_[r][6] + m.m_[r][7] + m.m_[r][8])
        + m.m_[r][9] * W + m.m_[r][10] * Z;
    return ans % K;
}

int main() {
    scanf("%ld%ld", &N, &K);
    scanf("%d%d%d%d", &P, &Q, &R, &T);
    scanf("%d%d%d", &U, &V, &W);
    scanf("%d%d%d", &X, &Y, &Z);
    Matrix m(11);
    m.set(0, 0, P);
    m.set(0, 1, 1);
    m.set(0, 2, 1);
    m.set(0, 3, Q);
    m.set(0, 6, 1);
    m.set(0, 7, T);
    m.set(0, 8, R);
    m.set(1, 0, 1);
    m.set(1, 1, U);
    m.set(1, 2, 1);
    m.set(1, 4, V);
    m.set(1, 9, 1);
    m.set(2, 0, 1);
    m.set(2, 1, 1);
    m.set(2, 2, X);
    m.set(2, 5, Y);
    m.set(2, 6, 2);
    m.set(2, 7, 1);
    m.set(2, 10, 1);
    m.set(3, 0, 1);
    m.set(4, 1, 1);
    m.set(5, 2, 1);
    m.set(6, 6, 1);
    m.set(7, 6, 1);
    m.set(7, 7, 1);
    m.set(8, 6, 1);
    m.set(8, 7, 2);
    m.set(8, 8, 1);
    m.set(9, 9, W);
    m.set(10, 10, Z);
    auto mn = Matrix::power(m, N-2);
    int64_t a = tally(mn, 0);
    int64_t b = tally(mn, 1);
    int64_t c = tally(mn, 2);
    printf("nodgd %ld\n", a);
    printf("Ciocio %ld\n", b);
    printf("Nicole %ld\n", c);
    return 0;
}
