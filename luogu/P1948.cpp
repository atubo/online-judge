// https://www.luogu.org/problem/show?pid=1948
// [USACO08JAN]电话线Telephone Lines

#include <bits/stdc++.h>
using namespace std;


// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt;
    };

    vector<int> head;
    vector<Edge> E;
    int eidx;
    int N;

    Graph(int N_, int M):N(N_) {
        head.resize(N);
        E.resize(M);
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

int N, P, K;
using PII = pair<int, int>;

const int INF = 0x7FFFFFFF;

bool dijkstra(const Graph& g, int lmax) {
    vector<int> dist(N, INF);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push(make_pair(0, 0));
    dist[0] = 0;
    while (!q.empty()) {
        PII p = q.top();
        q.pop();
        if (p.second == N-1) break;

        int u = p.second;
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            w = !(w <= lmax);
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q.push(make_pair(dist[v], v));
            }
        }
    }
    return dist[N-1] <= K;
}

int main() {
    scanf("%d%d%d", &N, &P, &K);
    Graph g(N, 2*P);
    int maxl = 0;
    for (int i = 0; i < P; i++) {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        a--; b--;
        g.addEdge(a, b, l);
        g.addEdge(b, a, l);
        maxl = max(maxl, l);
    }

    if (!dijkstra(g, maxl)) {
        printf("-1\n");
        return 0;
    }
    if (dijkstra(g, 0)) {
        printf("0\n");
        return 0;
    }
    int lo = 0, hi = maxl;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (dijkstra(g, mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);
    return 0;
}
