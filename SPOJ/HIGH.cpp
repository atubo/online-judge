// http://www.spoj.com/problems/HIGH/
// HIGH - Highways

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

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

int N, M;

void solve() {
    scanf("%d%d", &N, &M);
    if (N == 1) {
        printf("1\n");
        return;
    }

    Graph g(N, 2*M);
    vector<int> d(N);
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        g.addEdge(x, y);
        g.addEdge(y, x);
        d[x]++;
        d[y]++;
    }
    GaussianElimination ge(N-1);
    for (int i = 0; i < N-1; i++) {
        ge.A[i][i] = d[i];
        for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v != N-1) ge.A[i][v]--;
        }
    }
    ge.solve();
    double ans = 1;
    for (int i = 0; i < N-1; i++) {
        ans *= ge.A[i][i];
    }
    ans = abs(ans);
    printf("%lld\n", int64_t(ans+0.5));
}


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
