// https://www.luogu.org/problemnew/show/P3702
// [SDOI2017]序列计数

#include <bits/stdc++.h>
using namespace std;

const int MOD = 20170408;

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
                    tmp.m_[i][j] += (1LL*m_[i][k] * rhs.m_[k][j]) % MOD;
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

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);

        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    break;
                }
            }
        }
    }
};

const int MAXM = 20000010;
int N, M, P;
int ps[MAXM];

int64_t solve1() {
    Matrix m(P);
    for (int r1 = 0; r1 < P; r1++) {
        for (int r2 = 0; r2 < P; r2++) {
            int r3 = r2;
            if (r3 < r1) r3 += P;
            int d = r3 - r1;
            int k = 0;
            if (d <= M) {
                k = (M-(r3-r1)) / P + (r3 != r1);
            }
            m.m_[r2][r1] = k;
        }
    }
    auto mp = Matrix::power(m, N);
    return mp.m_[0][0];
}

int64_t solve2() {
    EulerSieve sieve(M);
    for (int i = 1; i <= M; i++) {
        ps[i] = sieve.isPrime[i];
        if (i > P) ps[i] += ps[i-P];
    }
    Matrix m(P);
    for (int r1 = 0; r1 < P; r1++) {
        for (int r2 = 0; r2 < P; r2++) {
            int r3 = r2;
            if (r3 < r1) r3 += P;
            int d = r3 - r1;
            if (d <= M) {
                int k = (M-d) / P;
                k -= ps[d+k*P];
                m.m_[r2][r1] = k + (r3 != r1);
            }
        }
    }
    auto mp = Matrix::power(m, N);
    return mp.m_[0][0];
}

int main() {
    scanf("%d%d%d", &N, &M, &P);
    int64_t ans1 = solve1();
    int64_t ans2 = solve2();
    printf("%ld\n", (ans1+MOD-ans2) % MOD);
    return 0;
}
