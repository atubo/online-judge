// https://www.luogu.org/problemnew/show/P4455
// [CQOI2018]社交网络

#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;
int INV[MOD];

int mul(int a, int b) {
    return (a * b) % MOD;
}

int sub(int a, int b) {
    return (a + MOD - b) % MOD;
}

class GaussianElimination {
public:
    // note this class owns A and X
    const int N;
    int **A;

    GaussianElimination(int N_): N(N_) {
        alloc();
    }

    ~GaussianElimination() {
        dealloc();
    }

    int solve() {
        int f = 1;
        for (int k = 0; k < N; k++) {
            // find principal
            int principal = A[k][k];
            int i0 = k;
            for (int i = k; i < N; i++) {
                if (A[i][k] > principal) {
                    principal = A[i][k];
                    i0 = i;
                }
            }
            // swap rows
            if (i0 != k) f = -f;
            for (int j = 0; j < N; j++) {
                swap(A[k][j], A[i0][j]);
            }

            if (A[k][k] == 0) return false;

            for (int i = k+1; i < N; i++) {
                A[i][k] = mul(A[i][k],  INV[A[k][k]]);
                for (int j = k+1; j < N; j++) {
                    A[i][j] = sub(A[i][j], mul(A[i][k], A[k][j]));
                }
            }
        }

        return f;
    }

private:
    void alloc() {
        A = new int*[N];
        for (int i = 0; i < N; i++) {
            A[i] = new int[N]{};
        }
    }

    void dealloc() {
        for (int i = 0; i < N; i++) {
            delete[] A[i];
        }
        delete[] A;
    }
};

const int MAXN = 256;
int N, M;
int C[MAXN][MAXN];

int main() {
    INV[1] = 1;
    for (int i = 2; i < MOD; i++) {
        INV[i] = mul((MOD - MOD/i), INV[MOD%i]);
    }

    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        C[a][a]++;
        C[b][a]--;
    }

    GaussianElimination gauss(N-1);
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            gauss.A[i-1][j-1] = ((C[i][j] % MOD) + MOD) % MOD;
        }
    }

    int f = gauss.solve();

    int ans = 1;
    for (int i = 0; i < N-1; i++) {
        ans = mul(ans, gauss.A[i][i]);
    }
    if (f == -1) ans = sub(MOD, ans);
    printf("%d\n", ans);

    return 0;
}
