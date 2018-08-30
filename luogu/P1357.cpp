// https://www.luogu.org/problemnew/show/P1357
// 花园

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int64_t N;
int M, K;
int MASK;

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

// square matrix fast power
class Matrix {
public:
    int **m_;
    int n_;

public:
    Matrix(int n): n_(n) {
        alloc();
    }

    Matrix(const Matrix &other) {
        n_ = other.n_;
        alloc();
        for (int i = 0; i < n_; i++) {
            memcpy(m_[i], other.m_[i], n_ * sizeof(int));
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
                printf("%d ", m_[i][j]);
            }
            printf("\n");
        }
    }

private:
    void alloc() {
        m_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            m_[i] = new int[n_]{};
        }
    }

    void mul(const Matrix &rhs, Matrix &tmp) {
        for (int i = 0; i < n_; i++) {
            memset(tmp.m_[i], 0, n_ * sizeof(int));
            for (int k = 0; k < n_; k++) {
                if (!m_[i][k]) continue;
                for (int j = 0; j < n_; j++) {
                    //tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j];
                    tmp.m_[i][j] = add(tmp.m_[i][j],
                                       ::mul(m_[i][k], rhs.m_[k][j]));
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
};

bool valid(int x) {
    return __builtin_popcount(x) <= K;
}

bool compatible(int x, int y) {
    for (int i = 1; i < M; i++) {
        int z = ((y << i) & MASK) | (x >> (M-i));
        if (__builtin_popcount(z) > K) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%ld%d%d", &N, &M, &K);
    MASK = (1<<M) - 1;
    Matrix m(1<<M);
    for (int i = 0; i < (1<<M); i++) {
        if (!valid(i)) continue;
        for (int t = 0; t < 2; t++) {
            int x = ((i << 1) & MASK)| t;
            if (valid(x)) {
                m.m_[x][i]++;
            }
        }
    }
    auto mp = Matrix::power(m, N-M);
    int64_t ans = 0;
    for (int start = 0; start < (1<<M); start++) {
        if (!valid(start)) continue;
        for (int end = 0; end < (1<<M); end++) {
            if (valid(end) && compatible(start, end)) {
                ans = add(ans, mp.m_[end][start]);
            }
        }
    }
    printf("%ld", ans);
    return 0;
}
