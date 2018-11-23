// https://www.luogu.org/problemnew/show/P2738
// [USACO4.1]篱笆回路Fence Loops

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

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int MAXN = 110;
int N;
bool vis[MAXN];

bool dfs(const Graph &g, int u, int target, int from, int rem) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v == from || w > rem) continue;
        if (v == target) return true;
        if (!vis[v]) {
            if (dfs(g, v, target, u, rem-w)) return true;
        }
    }
    return false;
}


bool check(const Graph &g, int mid) {
    for (int i = 0; i < N; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(g, i, i, -1, mid)) return true;
    }
    return false;
}

int main() {
    scanf("%d", &N);
    map<set<int>, int> nodeId;
    Graph g(2*N, 2*N);
    for (int i = 0; i < N; i++) {
        int s, l, n1, n2;
        scanf("%d%d%d%d", &s, &l, &n1, &n2);
        set<int> es1 = {s};
        set<int> es2 = {s};
        for (int j = 0; j < n1; j++) {
            int e;
            scanf("%d", &e);
            es1.insert(e);
        }
        if (nodeId.count(es1) == 0) {
            nodeId.insert(make_pair(es1, nodeId.size()));
        }
        for (int j = 0; j < n2; j++) {
            int e;
            scanf("%d", &e);
            es2.insert(e);
        }
        if (nodeId.count(es2) == 0) {
            nodeId.insert(make_pair(es2, nodeId.size()));
        }
        g.addEdge(nodeId[es1], nodeId[es2], l);
        g.addEdge(nodeId[es2], nodeId[es1], l);
    }

#if 0
    for (int i = 0; i < (int)nodeId.size(); i++) {
        printf("u=%d ", i);
        for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            printf("(%d %d) ", v, w);
        }
        printf("\n");
    }
#endif

    int lo = 0, hi = 255*N+1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(g, mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);

    return 0;
}
