// https://www.luogu.org/problem/show?pid=1939
// 数列

#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1000000007;

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

// square matrix fast power
class Matrix {
public:
    vector<vector<int>> _m;
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
                    ret._m[i][j] = add(ret._m[i][j],
                                       mul(_m[i][k], rhs._m[k][j]));
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

int main() {
    Matrix m(3);
    m._m[0][0] = m._m[0][2] = m._m[1][0] = m._m[2][1] = 1;

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n <= 3) {
            printf("%d\n", 1);
            continue;
        }

        Matrix ret = Matrix::power(m, n-3);
        printf("%d\n", add(ret._m[0][0], add(ret._m[0][1], ret._m[0][2])));
    }
    return 0;
}
