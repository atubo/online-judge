// https://www.luogu.org/problemnew/show/P3043
// [USACO12JAN]牛联盟Bovine Alliance

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

const int MAXN = 100010;
const int MOD = 1000000007;
int N, M;
bool vis[MAXN];

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

void dfs1(const Graph &g, int u, int &nv, int &ne) {
    nv++;
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        ne++;
        int v = g.E[eidx].to;
        if (!vis[v]) dfs1(g, v, nv, ne);
    }
}

int solve(const Graph &g, int u) {
    int ne = 0, nv = 0;
    dfs1(g, u, nv, ne);
    ne /= 2;
    if (ne > nv) return 0;
    if (ne == nv) return 2;
    return nv;
}
    

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    int64_t ans = 1;
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            int x = solve(g, i);
            if (x == 0) {
                ans = 0;
                break;
            }
            ans = mul(ans, x);
        }
    }
    printf("%ld\n", ans);

    return 0;
}
