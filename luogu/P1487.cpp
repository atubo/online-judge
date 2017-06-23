// https://www.luogu.org/problem/show?pid=1487
// 失落的成绩单

#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    double m[3][3];
};

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix ret;
    memset(ret.m, 0, sizeof(ret.m));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                ret.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return ret;
}

Matrix pwr(const Matrix& M, int n) {
    assert(n >= 1);
    Matrix ret = M;
    for (int i = 2; i <= n; i++) {
        ret = ret * M;
    }
    return ret;
}

int main() {
    int N, m;
    double d, A1, An;
    cin >> N >> m;
    cin >> d >> A1 >> An;

    if (m == 1) {
        printf("%.3lf\n", A1);
        return 0;
    }
    if (m == N) {
        printf("%.3lf\n", An);
        return 0;
    }

    Matrix M;
    memset(M.m, 0, sizeof(M.m));
    M.m[0][0] = -2;
    M.m[0][1] = 1;
    M.m[0][2] = 2;
    M.m[1][0] = M.m[2][2] = 1;

    Matrix Mn = pwr(M, N-2);
    double u = Mn.m[0][0], v = Mn.m[0][1], w = Mn.m[0][2];
    double x, y, z;
    if (m == 2) {
        x = 1; y = 0; z = 0;
    } else {
        Matrix Mm = pwr(M, m-2);
        x = Mm.m[0][0]; y = Mm.m[0][1]; z = Mm.m[0][2];
    }
    double am = x/u * An - (x/u * v - y) * A1 - (x/u * w - z) * d;
    printf("%.3lf\n", am);
    return 0;
}
