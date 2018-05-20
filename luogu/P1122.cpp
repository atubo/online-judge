// https://www.luogu.org/problemnew/show/P1122
// 最大子树和

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

const int MAXN = 16010;
int N;
int64_t A[MAXN];
int64_t dp[MAXN][2];
int64_t ans = INT_MIN;

int64_t max3(int64_t a, int64_t b, int64_t c) {
    return max(a, max(b, c));
}

void dfs(const Graph &g, int u, int fa) {
    int64_t x0 = INT_MIN;
    int64_t x1 = A[u];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            dfs(g, v, u);
            x0 = max3(x0, dp[v][0], dp[v][1]);
            if (dp[v][1] > 0) x1 += dp[v][1];
        }
    }
    ans = max3(ans, x0, x1);
    dp[u][0] = x0;
    dp[u][1] = x1;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    dfs(g, 0, -1);
    printf("%lld\n", ans);
    return 0;
}
