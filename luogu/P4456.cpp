// https://www.luogu.org/problemnew/show/P4456
// [CQOI2018]交错序列

#include <bits/stdc++.h>
using namespace std;

int N, A, B, M;

// square matrix fast power
class Matrix {
public:
    int64_t **m_;
    int n_;

public:
    Matrix(int n): n_(n) {
        alloc();
    }

    Matrix(const Matrix &other) {
        n_ = other.n_;
        alloc();
        for (int i = 0; i < n_; i++) {
            memcpy(m_[i], other.m_[i], n_ * sizeof(int64_t));
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

private:
    void alloc() {
        m_ = new int64_t*[n_]{};
        for (int i = 0; i < n_; i++) {
            m_[i] = new int64_t[n_]{};
        }
    }

    void mul(const Matrix &rhs, Matrix &tmp) {
        for (int i = 0; i < n_; i++) {
            memset(tmp.m_[i], 0, n_ * sizeof(int64_t));
            for (int k = 0; k < n_; k++) {
                if (!m_[i][k]) continue;
                for (int j = 0; j < n_; j++) {
                    tmp.m_[i][j] += (m_[i][k] * rhs.m_[k][j]);
                }
            }
            for (int j = 0; j < n_; j++) {
                tmp.m_[i][j] %= M;
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
};

int binom[200][200];

void build() {
    binom[0][0] = 1;
    for (int i = 1; i <= A+B; i++) {
        binom[i][0] = 1;
        for (int j = 1; j <= A+B; j++) {
            binom[i][j] = (binom[i-1][j-1] + binom[i-1][j]) % M;
        }
    }
}

int main() {
    scanf("%d%d%d%d", &N, &A, &B, &M);
    build();
    Matrix m(2*(A+B+1));

    for (int i = 0; i <= A+B; i++) {
        m.m_[2*i][2*i] = m.m_[2*i][2*i+1] = 1;
        for (int k = 0; k <= i; k++) {
            m.m_[2*i+1][2*k] = binom[i][k];
        }
    }
    auto mp = Matrix::power(m, N);

    int64_t f = (A & 1) ? -1 : 1;
    int64_t np = 1;
    int ans = 0;
    for (int i = 0; i <= A; i++) {
        int64_t t = (f * binom[A][i]) % M;
        (t *= np) %= M;
        int j = A + B - i;
        (t *= (mp.m_[2*j][0] + mp.m_[2*j+1][0])) %= M;
        t = (t + M) % M;
        (ans += t) %= M;
        np = (np * N) % M;
        f = -f;
    }
    printf("%d\n", ans);

    return 0;
}
