// https://www.luogu.org/problem/show?pid=1396
// 营救

#include <bits/stdc++.h>
using namespace std;


// Note graph node is 0-indexed
class Graph {
public:
    static const int MAXM = 40010;

    struct Edge {
        int next, to, wt;
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
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

int N, M, S, T;

bool bfs(const Graph &g, int x) {
    vector<bool> vis(N);
    queue<int> q;
    q.push(S);
    vis[S] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == T) return true;
        for (int eid = g.head[u]; eid != -1; eid = g.E[eid].next) {
            int v = g.E[eid].to;
            int w = g.E[eid].wt;
            if (w <= x && !vis[v]) {
                q.push(v);
                vis[v] = true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d%d", &N, &M, &S, &T);
    S--; T--;
    Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }

    int lo = -1, hi = 10000;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (bfs(g, mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);
    return 0;
}
