// https://www.luogu.org/problemnew/show/P1131
// [ZJOI2007]时态同步

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 1000010;
public:
    struct Edge {
        int next, to, wt;
    };

    vector<int> head;
    int eidx;
    int N;

    Edge *E;

    Graph(int N_):N(N_) {
        head.resize(N);
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
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int64_t INF = 1e12;
const int MAXN = 500010;
int N, S;
int64_t cost[MAXN], sync[MAXN];

void dfs(const Graph &g, int u, int fa) {
    cost[u] = 0;
    int64_t syncMax = -1, syncTotal = 0;
    int cnt = 0;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int t = g.E[eidx].wt;
        if (v != fa) {
            cnt++;
            dfs(g, v, u);
            cost[u] += cost[v];
            syncMax = max(syncMax, t + sync[v]);
            syncTotal += t + sync[v];
        }
    }
    if (cnt > 0) {
        sync[u] = syncMax;
        cost[u] += syncMax * cnt - syncTotal;
    }
}

int main() {
    scanf("%d%d", &N, &S);
    S--;
    Graph g(N);
    for (int i = 0; i < N-1; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        a--; b--;
        g.addEdge(a, b, t);
        g.addEdge(b, a, t);
    }
    dfs(g, S, -1);
    printf("%lld", cost[S]);
    return 0;
}
