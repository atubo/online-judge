// https://www.luogu.org/problemnew/show/P2973
// [USACO10HOL]赶小猪Driving Out the Piggi…

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

const int MAXN = 310;
int N, M, P, Q;
double R;
int deg[MAXN];

void solve(const Graph &g, GaussianElimination &ge) {
    for (int u = 0; u < N; u++) {
        ge.A[u][u] = 1;
        ge.X[u] = (u == 0);
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            ge.A[u][v] = (R - 1) / deg[v];
        }
    }
    ge.solve();
    for (int i = 0; i < N; i++) {
        printf("%.9f\n", ge.X[i] * R);
    }
}

int main() {
    scanf("%d%d%d%d", &N, &M, &P, &Q);
    R = double(P)/Q;
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        g.addEdge(b, a);
        deg[a]++;
        deg[b]++;
    }

    GaussianElimination ge(N);
    solve(g, ge);
    return 0;
}
