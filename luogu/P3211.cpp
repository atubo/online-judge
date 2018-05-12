// https://www.luogu.org/problemnew/show/P3211
// [HNOI2011]XOR和路径

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt;
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

    // assume 0-indexed
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
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

    void reset() {
        for (int i = 0; i < N; i++) {
            memset(A[i], 0, N * sizeof(double));
        }
        memset(X, 0, N * sizeof(double));
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

const int MAXN = 110;
int N, M;
int deg[MAXN];
double ans;

int id0(int u) {return 2*u;}
int id1(int u) {return 2*u + 1;}

void solve(const Graph &g, GaussianElimination &ge, int k) {
    ge.reset();
    ge.X[0] = 1;
    for (int u = 0; u < N; u++) {
        int u0 = id0(u), u1 = id1(u);
        ge.A[u0][u0] = ge.A[u1][u1] = 1;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            int v0 = id0(v), v1 = id1(v);
            double x = 1.0 / deg[v];
            if (v != N-1) {
                if ((w>>k) & 1) {
                    ge.A[u0][v1] -= x;
                    ge.A[u1][v0] -= x;
                } else {
                    ge.A[u0][v0] -= x;
                    ge.A[u1][v1] -= x;
                }
            }
        }
    }
    ge.solve();

    ans += ge.X[2*N-1] * (1<<k);
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        deg[u]++;
        if (v != u) {
            g.addEdge(v, u, w);
            deg[v]++;
        }
    }

    GaussianElimination ge(2*N);
    for (int k = 0; k < 31; k++) {
        solve(g, ge, k);
    }
    printf("%.3f\n", ans);

    return 0;
}
