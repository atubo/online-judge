// https://www.luogu.org/problem/show?pid=2233
// [HNOI2002] 公交车路线

#include <bits/stdc++.h>
using namespace std;

// square matrix
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
                    ret._m[i][j] += (_m[i][k] * rhs._m[k][j]) % 1000;
                }
            }
        }
        swap(ret);
        return *this;
    }

    void swap(Matrix &other) {
        _m.swap(other._m);
    }

    static Matrix power(const Matrix &x, int n) {
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
    int N;
    cin >> N;
    Matrix m(8);
    for (int i = 0; i < 8; i++) {
        if (i == 3) m._m[i][2] = 1;
        else if (i == 5) m._m[i][6] = 1;
        else m._m[i][(i+1)%8] = m._m[i][(i+7)%8] = 1;
    }
    Matrix ret = Matrix::power(m, N-1);
    printf("%d\n", (ret._m[0][3] + ret._m[0][5]) % 1000);
    return 0;
}
