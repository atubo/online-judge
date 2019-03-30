// https://www.luogu.org/problemnew/show/P2656
// 采蘑菇

#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
    struct Edge {
        int to, next, w1, w2;
        bool sign;  // bridge?
    };

public:
    class Graph {
    private:
        int edgenum;
    public:
        const int N;
        vector<int> head;
        vector<Edge> E;
    public:
        Graph(int N_): N(N_) {
            head.resize(N, -1);
            edgenum = 0;
        }

        void addEdge(int u, int v, int w1, int w2) {
            Edge e = {v, head[u], w1, w2, false};
            E.push_back(e);
            head[u] = edgenum++;
        }
        friend class TarjanSCC;
    };

public:
    Graph& g;
    const int N;
    int taj, top, Time;    // SCC index
    vector<int> belong; // node -> its component
    vector<bool> instack;
    vector<vector<int> > bcc;   // component -> all nodes in it
    vector<int> DFN;
    vector<int> low;
    vector<int> Stack;

    vector<int> in, out;        // in and out degrees of the new graph

    vector<int> cnt;

    TarjanSCC(Graph& g_):g(g_), N(g.N) {
        top = Time = 0;
        taj = 0;
        belong.resize(N, -1);
        instack.resize(N, false);
        DFN.resize(N, -1);
        low.resize(N, -1);
        Stack.resize(N, -1);
    }

    void dfs() {
        for (int i = 0; i < N; i++) {
            if (DFN[i] == -1) tarjan(i, i);
        }
    }

    Graph build() {
        // set up new graph
        Graph ng(taj);
        in.resize(taj, 0);
        out.resize(taj, 0);
        cnt.resize(taj, 0);

        for (int i = 0; i < g.N; i++) {
            for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
                int u = belong[i];
                int v = belong[g.E[eidx].to];
                int w1 = g.E[eidx].w1;
                int w2 = g.E[eidx].w2;
                if (u != v) {
                    ng.addEdge(u, v, w1, w2);
                    out[u]++;
                    in[v]++;
                } else {
                    cnt[u] += w2;
                }

            }
        }
        return ng;
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.E[i].next) {
            int v = g.E[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (DFN[u] < low[v]) {
                    g.E[i].sign = 1;   // it's bridge
                }
            } else if (instack[v]) low[u] = min(low[u], DFN[v]);
        }

        if (low[u] == DFN[u]) {
            int now;
            bcc.push_back(vector<int>());
            do {
                now = Stack[--top];
                instack[now] = false;
                belong[now] = taj;
                bcc[taj].push_back(now);
            } while (now != u);
            taj++;
        }
    }
};

int harvest(int w, double c) {
    int ret = 0;
    int t = w;
    while (t > 0) {
        ret += t;
        t *= c;
    }
    return ret;
}

const int MAXM = 200010;
int N, M, S;

void dfs(const TarjanSCC::Graph &g, int u, vector<bool>& vis,
         vector<int> &topo) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!vis[v]) dfs(g, v, vis, topo);
    }
    topo.push_back(u);
}

vector<int> toposort(const TarjanSCC::Graph &g) {
    const int n = g.N;
    vector<int> ret;
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(g, i, vis, ret);
        }
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    TarjanSCC::Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        double c;
        scanf("%d%d%d%lf", &u, &v, &w, &c);
        u--, v--;
        int w2 = harvest(w, c);
        g.addEdge(u, v, w, w2);
    }
    TarjanSCC scc(g);
    scc.dfs();
    auto g2 = scc.build();
    auto topo = toposort(g2);
    vector<int> dp(g2.N, 0);
    for (int u: topo) {
        dp[u] = scc.cnt[u];
        int mx = 0;
        for (int eidx = g2.head[u]; ~eidx; eidx = g2.E[eidx].next) {
            int v = g2.E[eidx].to;
            mx = max(mx, dp[v]+g2.E[eidx].w1);
        }
        dp[u] += mx;
    }
    int s;
    scanf("%d", &s);
    printf("%d", dp[scc.belong[s-1]]);
    return 0;
}
