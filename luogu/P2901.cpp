// https://www.luogu.org/problemnew/show/P2901
// [USACO08MAR]牛慢跑Cow Jogging

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

int N, M, K;

void dfs(const Graph &g, int u, vector<bool> &vis, stack<int> &st) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!vis[v]) dfs(g, v, vis, st);
    }
    st.push(u);
}

vector<int> topoSort(const Graph &g) {
    stack<int> st;
    vector<bool> vis(N);
    for (int i = 0; i < N; i++) {
        if (!vis[i]) dfs(g, i, vis, st);
    }
    vector<int> ret;
    while (!st.empty()) {
        ret.push_back(st.top());
        st.pop();
    }
    return ret;
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    Graph g(N, M);
    for (int i = 0; i < M; i++) {
        int x, y, d;
        scanf("%d%d%d", &x, &y, &d);
        x--; y--;
        g.addEdge(x, y, d);
    }

    vector<int> topo = topoSort(g);
    reverse(topo.begin(), topo.end());

    vector<vector<int>> dist(N);
    for (int u: topo) {
        if (u == 0) {
            dist[u].push_back(0);
            continue;
        }
        vector<int> &d = dist[u];
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            for (int dn: dist[v]) {
                d.push_back(dn+w);
            }
        }
        if ((int)d.size() <= K) {
            sort(d.begin(), d.end());
        } else {
            partial_sort(d.begin(), d.begin()+K, d.end());
            d.erase(d.begin()+K, d.end());
        }
        if (u == N-1) break;
    }
    for (int i = 0; i < K; i++) {
        printf("%d\n", (i < (int)dist[N-1].size() ? dist[N-1][i]: -1));
    }

    return 0;
}
