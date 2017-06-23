// https://www.luogu.org/problem/show?pid=1487
// 失落的成绩单

#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    Matrix() {
        m.resize(3);
        for (int i = 0; i < 3; i++) {
            m[i].resize(3, 0);
        }
    }
    vector<vector<long double>> m;
};

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix ret;
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
    //assert(n >= 1);
    Matrix ret = M;
    for (int i = 2; i <= n; i++) {
        ret = ret * M;
    }
    return ret;
}

const int MAXN = 1005;
typedef long double ld;
ld A[MAXN];

int main() {
    int N, m;
    long double d;
    cin >> N >> m;
    cin >> d >> A[1] >> A[N];

    if (N == 3) {
        A[2] = (A[1] - A[3]) / 2 + d;
        printf("%.3lf\n", A[m]);
        return 0;
    }
    if (N <= 2) {
        printf("%.3lf\n", A[m]);
        return 0;
    }

    Matrix M;
    M.m[0][0] = -2;
    M.m[0][1] = 1;
    M.m[0][2] = 2;
    M.m[1][0] = M.m[2][2] = 1;

    Matrix Mn = pwr(M, N-2);
    long double u = Mn.m[0][0], v = Mn.m[0][1], w = Mn.m[0][2];
    A[2] = (A[N] - v * A[1] - w * d) / u;

    for (int i = 3; i <= m; i++) {
        A[i] = A[i-2] - 2 * A[i-1] + 2 * d;
    }
    printf("%.3llf\n", A[m]);
    return 0;
}
