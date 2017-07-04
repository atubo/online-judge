// https://www.luogu.org/problem/show?pid=2017
// [USACO09DEC]晕牛Dizzy Cows

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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

vector<int> topoSort(const Graph& g, vector<int>& d) {
    const int N = g.N;
    vector<int> topo(N);
    int cnt = 0;

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (!d[i]) {
            q.push(i);
            topo[i] = cnt++;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (!(--d[v])) {
                q.push(v);
                topo[v] = cnt++;
            }
        }
    }
    return topo;
}

using PII = pair<int, int>;

int main() {
    int N, P1, P2;
    scanf("%d%d%d", &N, &P1, &P2);
    Graph g(N, P1);
    int a, b;
    vector<int> d(N);
    for (int i = 0; i < P1; i++) {
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        d[b]++;
    }

    vector<PII> undirected;
    for (int i = 0; i < P2; i++) {
        scanf("%d%d", &a, &b);
        a--; b--;
        undirected.push_back(make_pair(a, b));
    }

    vector<int> topo = topoSort(g, d);

    for (const auto& e: undirected) {
        tie(a, b) = e;
        if (topo[a] > topo[b]) swap(a, b);
        printf("%d %d\n", a+1, b+1);
    }
    return 0;
}
