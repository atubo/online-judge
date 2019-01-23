// https://www.luogu.org/problemnew/show/P2962
// [USACO09NOV]灯Lights

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

int N, M;
int64_t ALL;
int64_t masks[40];
int ans1 = INT_MAX, ans2 = INT_MAX;
map<int64_t, int> mp;

void dfs1(const Graph &g, int u, int64_t mask, int d) {
    if (u > (N+1)/2) return;
    if (mask == ALL) {
        ans1 = min(ans1, d);
        return;
    }

    if (mp.count(mask) == 0) {
        mp[mask] = d;
    } else {
        mp[mask] = min(mp[mask], d);
    }
    dfs1(g, u+1, mask^masks[u], d+1);
    dfs1(g, u+1, mask, d);
}

void dfs2(const Graph &g, int u, int64_t mask, int d) {
    if (u < (N-1)/2) return;
    if (mp.count(mask) > 0) {
        ans2 = min(ans2, d+mp[mask]);
    }
    dfs2(g, u-1, mask^masks[u], d+1);
    dfs2(g, u-1, mask, d);
}

void init(const Graph &g) {
    for (int u = 0; u < N; u++) {
        masks[u] = (1LL << u);
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            masks[u] |= (1LL << v);
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    ALL = (1LL<<N) - 1;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    init(g);
    dfs1(g, 0, 0, 0);
    if (ans1 != INT_MAX) {
        printf("%d", ans1);
    } else {
        dfs2(g, N-1, ALL, 0);
        printf("%d", ans2);
    }
    return 0;
}
