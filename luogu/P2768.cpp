// https://www.luogu.org/problemnew/show/P2768
// 珍珠项链

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1234567891;
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

    void print() const {
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < n_; j++) {
                printf("%ld ", m_[i][j]);
            }
            printf("\n");
        }
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
                    (tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j]) %= MOD;
                    (tmp.m_[i][j] += MOD) %= MOD;
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
};

int T, N, K;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &K);
        Matrix m(2*K+2);
        for (int j = 1; j <= K; j++) {
            m.m_[j][j-1] = K - j + 1;
            m.m_[j][j] = 1 + j;
            m.m_[j][K+j] = - (K - j + 1);
            m.m_[j][K+1+j] = -j;
        }
        for (int i = K+1; i < 2*K+2; i++) {
            m.m_[i][i-K-1] = 1;
        }
        auto ret = Matrix::power(m, N-1);
        printf("%ld\n", (ret.m_[K][1] * K) % MOD);


    }
    return 0;
}
