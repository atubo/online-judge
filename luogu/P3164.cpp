// https://www.luogu.org/problemnew/show/P3164
// [CQOI2014]和谐矩阵

#include <bits/stdc++.h>
using namespace std;

class GaussianElimination {
public:
    // note this class owns A and X
    const int N;
    int **A;
    int *X;

    GaussianElimination(int N_): N(N_) {
        alloc();
    }

    ~GaussianElimination() {
        dealloc();
    }

    void solve() {
        int kmax = N;
        for (int k = 0; k < N; k++) {
            // find principal
            int i0 = -1;
            for (int i = k; i < N; i++) {
                if ((A[i][k]) == 1) {
                    i0 = i;
                }
            }
            if (i0 == -1) {
                kmax = k;
                break;
            }
            // swap rows
            for (int j = 0; j < N; j++) {
                swap(A[k][j], A[i0][j]);
            }
            swap(X[k], X[i0]);

            for (int i = k+1; i < N; i++) {
                if (A[i][k] == 0) continue;
                for (int j = k; j < N; j++) {
                    A[i][j] ^= A[k][j];
                }
                X[i] ^= X[k];
            }
        }

        for (int k = kmax; k < N; k++) {
            X[k] = 1;
        }

        // backward step
        for (int i = kmax-1; i >= 0; i--) {
            for (int j = i+1; j < N; j++) {
                X[i] ^= A[i][j] * X[j];
            }
        }
    }

private:
    void alloc() {
        A = new int*[N];
        for (int i = 0; i < N; i++) {
            A[i] = new int[N]{};
        }
        X = new int[N]{};
    }

    void dealloc() {
        for (int i = 0; i < N; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] X;
    }
};

int N, M;
const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {1, 0, -1, 0};

int id(int r, int c) {
    return r*M + c;
}

bool inRange(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < M;
}

void solve() {
    GaussianElimination ge(N*M);
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int e1 = id(r, c);
            ge.A[e1][e1] = 1;
            for (int d = 0; d < 4; d++) {
                int r2 = r + DX[d];
                int c2 = c + DY[d];
                if (inRange(r2, c2)) {
                    int e2 = id(r2, c2);
                    ge.A[e1][e2] = 1;
                }
            }
        }
    }
    ge.solve();
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int idx = r * M + c;
            printf("%d ", ge.X[idx]);
        }
        printf("\n");
    }
}

int main() {
    scanf("%d%d", &N, &M);
    solve();
    return 0;
}
