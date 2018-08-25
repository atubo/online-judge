// https://www.luogu.org/problemnew/show/P2461
// [SDOI2008]递归数列

#include <bits/stdc++.h>
using namespace std;

int P;
int add(int64_t a, int64_t b) {
    return (a + b) % P;
}

int sub(int64_t a, int64_t b) {
    return (a - b + P) % P;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % P;
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
        Matrix ret(x.n_), temp(x.n_);
        for (int i = 0; i < x.n_; i++) ret.m_[i][i] = 1;
        while (n) {
            if (n & 1) ret.mul(x, temp);
            x.mul(x, temp);
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

    void mul(const Matrix &rhs, Matrix &temp) {
        for (int i = 0; i < n_; i++) {
            memset(temp.m_[i], 0, n_ * sizeof(int));
            for (int k = 0; k < n_; k++) {
                if (!m_[i][k]) continue;
                for (int j = 0; j < n_; j++) {
                    temp.m_[i][j] = add(temp.m_[i][j],
                                       ::mul(m_[i][k], rhs.m_[k][j]));
                }
            }
        }
        swap(temp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }
};

const int MAXK = 18;
int K;
int B[MAXK], C[MAXK], S[MAXK];
int64_t M, N;

int solve(const Matrix &mat, int64_t m) {
    if (m <= K) return S[m];
    auto mp = Matrix::power(mat, m-K);
    int64_t ans = 0;
    for (int i = 0; i <= K; i++) {
        ans = add(ans, mul(mp.m_[0][i], S[K-i]));
    }
    return ans;
}

int main() {
    scanf("%d", &K);
    for (int i = 1; i <= K; i++) {
        scanf("%d", &B[i]);
    }
    for (int i = 1; i <= K; i++) {
        scanf("%d", &C[i]);
    }
    scanf("%ld%ld%d", &M, &N, &P);
    for (int i = 1; i <= K; i++) {
        S[i] = add(S[i-1], B[i]);
    }
    Matrix m(K+1);
    m.m_[0][0] = (1 + C[1]) % P;
    for (int i = 1; i < K; i++) {
        m.m_[0][i] = sub(C[i+1]%P, C[i]%P);
    }
    m.m_[0][K] = ((P - C[K]) % P + P) % P;
    for (int i = 1; i <= K; i++) {
        m.m_[i][i-1] = 1;
    }
    int64_t ans = sub(solve(m, N), solve(m, M-1));
    printf("%ld", ans);
    return 0;
}
