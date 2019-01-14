// https://www.luogu.org/problemnew/show/P3204
// [HNOI2010]公交线路

#include <bits/stdc++.h>
using namespace std;

int MOD = 30031;

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
                    (tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j]) %= MOD;
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
};

int toId[1024], toMask[128];
int N, K, P;
int M;

void init() {
    for (int s = (1<<(P-1)); s < (1<<P); s++) {
        if (__builtin_popcount(s) == K) {
            toId[s] = M;
            toMask[M] = s;
            M++;
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &K, &P);
    init();
    Matrix m(M);
    for (int i = 0; i < M; i++) {
        int s1 = (toMask[i]-(1<<(P-1))) << 1;
        for (int j = 0; j < M; j++) {
            int s2 = toMask[j];
            if (__builtin_popcount(s1&s2) == K-1) {
                m.m_[j][i] = 1;
            }
        }
    }

    auto mp = Matrix::power(m, N-K);
    int id = toId[((1<<K)-1)<<(P-K)];
    printf("%d\n", mp.m_[id][id]);

    return 0;
}
