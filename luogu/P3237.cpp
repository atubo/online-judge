// https://www.luogu.org/problem/show?pid=3237
// [HNOI2014]米特运输

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 500010;
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    vector<int> out;
    int eidx;
    int N;

    Edge *E;

    Graph(int N_):N(N_) {
        head.resize(N);
        out.resize(N, 0);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[MAXM]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        out[u]++;
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 500010;
int N;
double A[MAXN], B[MAXN], C[MAXN];

void dfs(const Graph &g, int u) {
    double c = 0;
    if (g.out[u] >= 2) {
        c = log(g.out[u]);
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        B[v] = B[u] - c;
        dfs(g, v);
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lf", &A[i]);
        A[i] = log(A[i]);
    }
    Graph g(N);
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
    }
    dfs(g, 0);

    for (int i = 0; i < N; i++) {
        C[i] = A[i] - B[i];
    }
    sort(C, C+N);
    const double tol = 1e-10;
    int lastp = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (fabs(C[i] - C[lastp]) > tol) {
            ans = max(ans, i - lastp);
            lastp = i;
        }
    }
    ans = max(ans, N-lastp);
    printf("%d\n", N-ans);

    return 0;
}
