// https://www.luogu.org/problem/show?pid=2850
// [USACO06DEC]虫洞Wormholes

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 5300;
public:
    struct Edge {
        int next, from, to, wt;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].from = u;
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

int main() {
    int F;
    scanf("%d", &F);
    while (F--) {
        int N, M, W;
        scanf("%d%d%d", &N, &M, &W);
        Graph g(N);
        int u, v, w;
        for (int i = 0; i < M; i++) {
            scanf("%d%d%d", &u, &v, &w);
            u--; v--;
            g.addEdge(u, v, w);
            g.addEdge(v, u, w);
        }
        for (int i = 0; i < W; i++) {
            scanf("%d%d%d", &u, &v, &w);
            u--; v--;
            g.addEdge(u, v, -w);
        }

        vector<int> d(N, INT_MAX/2);
        d[0] = 0;
        int i;
        for (i = 0; i < N; i++) {
            bool updated = false;
            for (int j = 0; j < g.eidx; j++) {
                u = g.E[j].from;
                v = g.E[j].to;
                w = g.E[j].wt;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    updated = true;
                }
            }
            if (!updated) break;
        }
        printf(i < N ? "NO\n" : "YES\n");
    }
    return 0;
}
