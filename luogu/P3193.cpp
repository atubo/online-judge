// https://www.luogu.org/problemnew/show/P3193
// [HNOI2008]GT考试

#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int A[22][10];

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
                    ret._m[i][j] = (ret._m[i][j] + _m[i][k] * rhs._m[k][j]) % K;
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

class KMP {
public:
    KMP(const string& str):f(str.length(), 0) {
        int t = 0;
        f[0] = 0;

        // prefix function
        for (int s = 1; s < (int)str.length(); s++) {
            while (t > 0 && str[s] != str[t]) {
                t = f[t-1];
            }
            if (str[s] == str[t]) {
                t++;
            }
            f[s] = t;
        }
    }

    int operator[](int i) const {
        return f[i];
    }

private:
    vector<int> f;
};

void buildTransition(const KMP &kmp, const string &s) {
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= 9; j++) {
            int t = (i == M ? kmp[i-1] : i);
            while (t > 0 && s[t] != '0' + j) {
                t = kmp[t-1];
            }
            A[i][j] = t + (s[t] == '0' + j);
        }
    }
}

void buildMatrix(Matrix &m) {
    for (int i = 0; i < M; i++) {
        for (int k = 0; k <= 9; k++) {
            int j = A[i][k];
            if (j < M) {
                m._m[j][i] = (m._m[j][i] + 1) % K;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    string s;
    cin >> s;
    KMP kmp(s);
    buildTransition(kmp, s);

    Matrix m(M);
    buildMatrix(m);

    Matrix ret = Matrix::power(m, N);
    int ans = 0;
    for (int i = 0; i < M; i++) {
        ans = (ans + ret._m[i][0]) % K;
    }
    printf("%d\n", ans);
    return 0;
}
