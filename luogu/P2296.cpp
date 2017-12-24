// https://www.luogu.org/problemnew/show/P2296
// 寻找道路

#include <bits/stdc++.h>
using namespace std;


// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    vector<Edge> E;
    int eidx;
    int N, M;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        E.resize(M);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 10010;
int N, M, S, T;
bool vis[MAXN], disq[MAXN];

void dfs(const Graph &g, int u) {
    vis[u] = true;
    for (int eid = g.head[u]; eid != -1; eid = g.E[eid].next) {
        int v = g.E[eid].to;
        if (!vis[v]) dfs(g, v);
    }
}

void mark(const Graph &g) {
    vector<int> d;
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            d.push_back(i);
            disq[i] = true;
        }
    }
    for (int x: d) {
        for (int eid = g.head[x]; eid != -1; eid = g.E[eid].next) {
            int v = g.E[eid].to;
            disq[v] = true;
        }
    }
}

int bfs(const Graph &g) {
    using PII = pair<int, int>;
    if (disq[S]) return -1;
    queue<PII> q;
    vector<bool> visited(N);
    q.push(make_pair(S, 0));
    visited[S] = true;
    while (!q.empty()) {
        int u, d;
        tie(u, d) = q.front();
        if (u == T) return d;
        q.pop();
        for (int eid = g.head[u]; eid != -1; eid = g.E[eid].next) {
            int v = g.E[eid].to;
            if (!visited[v] && !disq[v]) {
                q.push(make_pair(v, d+1));
                visited[v] = true;
            }
        }
    }
    return -1;
}
    

int main() {
    scanf("%d%d", &N, &M);
    Graph g1(N, M), g2(N, M);
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        g1.addEdge(x, y);
        g2.addEdge(y, x);
    }
    scanf("%d%d", &S, &T);
    S--; T--;

    dfs(g2, T);
    mark(g2);

    printf("%d\n", bfs(g1));

    return 0;
}
