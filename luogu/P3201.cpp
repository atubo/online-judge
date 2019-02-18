// https://www.luogu.org/problemnew/show/P3201
// [HNOI2009]梦幻布丁

#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int N;
    vector<unordered_map<int, int>> adj;
    vector<set<int>> in;

    Graph(int N_): N(N_), adj(N_), in(N_) {}

    void addEdge(int u, int v, int w) {
        adj[u][v] += w;
        in[v].insert(u);
    }
};

const int MAXN = 1e5+10;
const int MAXA = 1e6+10;
int N, M;
int A[MAXN], A2[MAXN];
int C[MAXA];
int tot;

int merge(Graph &g, int u, int v) {
    if (g.adj[u].count(v) > 0) {
        tot -= g.adj[u][v];
    }
    if (g.adj[v].count(u) > 0) {
        tot -= g.adj[v][u];
    }

    if (g.adj[u].size() + g.in[u].size() >
        g.adj[v].size() + g.in[v].size()) {
        swap(u, v);
    }

    for (int p: g.in[u]) {
        int w = g.adj[p][u];
        g.adj[p][v] += w;
        g.adj[p].erase(u);
        g.in[v].insert(p);
    }
    g.in[u].clear();

    for (const auto &pr: g.adj[u]) {
        int p = pr.first;
        int w = pr.second;
        g.adj[v][p] += w;
        g.in[p].erase(u);
        g.in[p].insert(v);
    }
    g.adj[u].clear();

    return v;
}

int main() {
    memset(C, -1, sizeof(C));
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A2[i] = A[i];
    }
    sort(A2, A2+N);
    auto endp = unique(A2, A2+N);
    const int nc = endp - A2;
    for (int i = 0; i < N; i++) {
        int t = A[i];
        A[i] = lower_bound(A2, endp, A[i]) - A2;
        C[t] = A[i];
    }

    Graph g(nc);
    tot = 1;
    for (int i = 1; i < N; i++) {
        if (A[i] != A[i-1]) {
            g.addEdge(A[i-1], A[i], 1);
            tot++;
        }
    }

    for (int i = 0; i < M; i++) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 2) {
            printf("%d\n", tot);
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            int u = C[x], v = C[y];
            if (u == -1) continue;
            if (v == -1) {
                swap(C[x], C[y]);
                continue;
            }
            if (u == v) continue;
            int p = merge(g, u, v);
            C[x] = -1;
            C[y] = p;
        }
    }
    return 0;
}
