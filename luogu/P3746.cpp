// https://www.luogu.org/problemnew/solution/P3746
// [六省联考2017]组合数问题

#include <bits/stdc++.h>
using namespace std;

int P;

// square matrix fast power
class Matrix {
public:
    vector<vector<int64_t>> _m;
    int _n;

public:
    Matrix(int n): _n(n) {
        _m.resize(n);
        for (int i = 0; i < n; i++) {
            _m[i].resize(n);
        }
    }

    Matrix& operator *= (const Matrix &rhs) {
        Matrix ret(_n);
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++) {
                for (int k = 0; k < _n; k++) {
                    ret._m[i][j] += (_m[i][k] * rhs._m[k][j]) % P;
                    ret._m[i][j] %= P;
                }
            }
        }
        swap(ret);
        return *this;
    }

    void swap(Matrix &other) {
        _m.swap(other._m);
    }

    static Matrix power(const Matrix &x, int64_t n) {
        if (n == 1) return x;
        Matrix y = power(x, n/2);
        y *= y;
        if (n & 1) y *= x;
        return y;
    }

    void print() const {
        for (int i = 0; i < _n; i++) {
            for (int x: _m[i]) {
                printf("%d ", x);
            }
            printf("\n");
        }
    }
};

int N, K, R;

int main() {
    scanf("%d%d%d%d", &N, &P, &K, &R);
    Matrix m(K);

    for (int i = 0; i < K; i++) {
        ++m._m[i][i];
        ++m._m[i][(i+K-1)%K];
    }

    auto res = Matrix::power(m, int64_t(N) * K);
    printf("%lld", res._m[R][0]);

    return 0;
}
