// https://www.luogu.org/problemnew/show/P3706
// [SDOI2017]硬币游戏

#include <bits/stdc++.h>
using namespace std;

class GaussianElimination {
public:
    // note this class owns A and X
    const int N;
    long double **A;
    long double *X;

    static constexpr long double EPSLON = 1e-100;

    GaussianElimination(int N_): N(N_) {
        alloc();
    }

    ~GaussianElimination() {
        dealloc();
    }

    bool solve() {
        for (int k = 0; k < N; k++) {
            // find principal
            auto principal = fabs(A[k][k]);
            int i0 = k;
            for (int i = k; i < N; i++) {
                if (fabs(A[i][k]) > principal) {
                    principal = fabs(A[i][k]);
                    i0 = i;
                }
            }
            // swap rows
            for (int j = 0; j < N; j++) {
                swap(A[k][j], A[i0][j]);
            }
            swap(X[k], X[i0]);

            if (fabs(A[k][k]) < EPSLON) return false;

            for (int i = k+1; i < N; i++) {
                A[i][k] = A[i][k] / A[k][k];
                for (int j = k+1; j < N; j++) {
                    A[i][j] = A[i][j] - A[i][k] * A[k][j];
                }
                X[i] = X[i] - A[i][k] * X[k];
            }
        }

        // backward step
        for (int i = N-1; i >= 0; i--) {
            for (int j = i+1; j < N; j++) {
                X[i] = X[i] - A[i][j] * X[j];
            }
            X[i] = X[i] / A[i][i];
        }
        return true;
    }

private:
    void alloc() {
        A = new long double*[N];
        for (int i = 0; i < N; i++) {
            A[i] = new long double[N]{};
        }
        X = new long double[N]{};
    }

    void dealloc() {
        for (int i = 0; i < N; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] X;
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

int N, M;

long double coeff(const string &p, const string &q) {
    KMP kmp(p);
    int t = 0;
    for (int i = 0; i < M; i++) {
        while (t > 0 && q[i] != p[t]) t = kmp[t-1];
        if (q[i] == p[t]) t++;
    }
    if (t == M) t = kmp[t-1];
    if (t == 0) return 0;
    long double ret = 0;
    while (t > 0) {
        ret += pow((long double)(0.5), M-t);
        t = kmp[t-1];
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    vector<string> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    GaussianElimination ge(N+1);
    for (int i = 0; i < N; i++) {
        ge.A[i][i] = 1;
        for (int j = 0; j < N; j++) {
            ge.A[i][j] += coeff(S[i], S[j]);
        }
        ge.A[i][N] = -pow((long double)(0.5), M);
    }
    ge.X[N] = 1;
    for (int i = 0; i < N; i++) {
        ge.A[N][i] = 1;
    }
    ge.solve();
    for (int i = 0; i < N; i++) {
        printf("%.8Lf\n", ge.X[i]);
    }

    return 0;
}
