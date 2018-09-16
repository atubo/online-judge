// https://www.luogu.org/problemnew/show/P3119
// [USACO15JAN]草鉴定Grass Cownoisseur

#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
    struct Edge {
        int to, next;
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

        void addEdge(int u, int v) {
            Edge e = {v, head[u], false};
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

        for (int i = 0; i < g.N; i++) {
            for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
                int u = belong[i];
                int v = belong[g.E[eidx].to];
                if (u != v) {
                    ng.addEdge(u, v);
                    out[u]++;
                    in[v]++;
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

// Note: be sure it's DAG
class TopologicalSort {
public:
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(const TarjanSCC::Graph &g,
                             int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = g.head[v]; i != -1; i = g.E[i].next) {
            int m = g.E[i].to;
            if (!visited[m]) {
                topologicalSortUtil(g, m, visited, order);
            }
        }

        order.push(v);
    }

public:
    TopologicalSort() {}

    void sort(const TarjanSCC::Graph &g) {
        const int N = g.N;
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(g, i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

void solve1(const TarjanSCC::Graph &g,
            int s,
            const vector<int> &topo,
            const vector<int> &wt,
            vector<int> &dp) {
    const int n = dp.size();
    dp[topo[s]] = wt[topo[s]];
    for (int i = s; i < n; i++) {
        int u = topo[i];
        if (dp[u] == 0) continue;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            dp[v] = max(dp[v], dp[u] + wt[v]);
        }
    }
}

TarjanSCC::Graph reverseGraph(const TarjanSCC::Graph &g) {
    TarjanSCC::Graph gr(g.N);
    for (int u = 0; u < g.N; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            gr.addEdge(v, u);
        }
    }
    return gr;
}

void solve2(const TarjanSCC::Graph &g,
            int s,
            const vector<int> &topo,
            const vector<int> &wt,
            vector<int> &dp) {
    dp[topo[s]] = wt[topo[s]];
    for (int i = s; i >= 0; i--) {
        int u = topo[i];
        if (dp[u] == 0) continue;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            dp[v] = max(dp[v], dp[u] + wt[v]);
        }
    }
}


int N, M;

int main() {
    scanf("%d%d", &N, &M);
    TarjanSCC::Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
    }
    TarjanSCC scc(g);
    scc.dfs();
    auto ng = scc.build();
    if (scc.taj == 1) {
        printf("%d\n", N);
        return 0;
    }
    vector<int> wt(scc.taj);
    for (int i = 0; i < scc.taj; i++) {
        wt[i] = scc.bcc[i].size();
    }

    TopologicalSort topo;
    topo.sort(ng);

    int pivot = 0;
    for (int i = 0; i < scc.taj; i++) {
        if (topo.topo[i] == scc.belong[0]) {
            pivot = i;
            break;
        }
    }

    vector<int> dp1(scc.taj, 0), dp2(scc.taj, 0);
    solve1(ng, pivot, topo.topo, wt, dp1);

    TarjanSCC::Graph ngr = reverseGraph(ng);
    solve2(ngr, pivot, topo.topo, wt, dp2);

    int ans = 0;
    for (int u = 0; u < scc.taj; u++) {
        for (int eidx = ng.head[u]; ~eidx; eidx = ng.E[eidx].next) {
            int v = ng.E[eidx].to;
            if (dp1[v] > 0 && dp2[u] > 0) {
                ans = max(ans, dp1[v] + dp2[u] - wt[scc.belong[0]]);
            } else if (dp1[u] > 0 && dp2[v] > 0) {
                ans = max(ans, dp1[u] + dp2[v] - wt[scc.belong[0]]);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
