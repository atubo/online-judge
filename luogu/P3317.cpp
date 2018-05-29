// https://www.luogu.org/problemnew/show/P3317
// [SDOI2014]重建

#include <bits/stdc++.h>
using namespace std;

class GaussianElimination {
public:
    // note this class owns A and X
    const int N;
    double **A;
    double *X;

    static constexpr double EPSLON = 1e-7;

    GaussianElimination(int N_): N(N_) {
        alloc();
    }

    ~GaussianElimination() {
        dealloc();
    }

    bool solve() {
        for (int k = 0; k < N; k++) {
            // find principal
            double principal = fabs(A[k][k]);
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
        A = new double*[N];
        for (int i = 0; i < N; i++) {
            A[i] = new double[N]{};
        }
        X = new double[N]{};
    }

    void dealloc() {
        for (int i = 0; i < N; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] X;
    }
};

const int MAXN = 52;
const double EPS = 1e-7;
double A[MAXN][MAXN];
int N;

int main() {
    scanf("%d", &N);
    double fac = 1;
    for (int i = 0; i < N; i++) {
        double dia = 0;
        for (int j = 0; j < N; j++) {
            scanf("%lf", &A[i][j]);
            A[i][j] = min(A[i][j], 1-EPS);
            if (i < j) fac *= (1 - A[i][j]);
            A[i][j] /= (1 - A[i][j]);
            dia += A[i][j];
        }
        A[i][i] = -dia;
    }
    GaussianElimination ge(N-1);
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-1; j++) {
            ge.A[i][j] = A[i][j];
        }
    }
    ge.solve();
    double det = 1;
    for (int i = 0; i < N-1; i++) {
        det *= ge.A[i][i];
    }
    printf("%.10f\n", fabs(det * fac));
    return 0;
}
