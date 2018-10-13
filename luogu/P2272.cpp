// https://www.luogu.org/problemnew/show/P2272
// [ZJOI2007]最大半连通子图

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
    void topologicalSortUtil(const TarjanSCC::Graph &g, int v, bool visited[],
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

const int MAXN = 100010;
int N, M, X;
int dp1[MAXN], dp2[MAXN];
bool vis[MAXN];

int add(int64_t a, int64_t b) {
    return (a + b) % X;
}

int main() {
    scanf("%d%d%d", &N, &M, &X);
    TarjanSCC::Graph g(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
    }
    TarjanSCC tarjan(g);
    tarjan.dfs();
    TarjanSCC::Graph ng = tarjan.build();
    TopologicalSort topo;
    topo.sort(ng);

    for (int i = (int)topo.topo.size()-1; i >= 0; i--) {
        int x = topo.topo[i];
        dp1[x] = tarjan.bcc[x].size();
        int mx = 0;
        for (int eidx = ng.head[x]; ~eidx; eidx = ng.E[eidx].next) {
            int y = ng.E[eidx].to;
            mx = max(mx, dp1[y]);
        }
        dp1[x] += mx;
    }

    for (int i = (int)topo.topo.size()-1; i >= 0; i--) {
        int x = topo.topo[i];
        for (int eidx = ng.head[x]; ~eidx; eidx = ng.E[eidx].next) {
            int y = ng.E[eidx].to;
            if (!vis[y]) {
                if (dp1[x] - dp1[y] == (int)tarjan.bcc[x].size()) {
                    dp2[x] = add(dp2[x], dp2[y]);
                }
                vis[y] = true;
            }
        }
        dp2[x] = max(1, dp2[x]);
        for (int eidx = ng.head[x]; ~eidx; eidx = ng.E[eidx].next) {
            int y = ng.E[eidx].to;
            vis[y] = false;
        }
    }

    int ans1 = 0;
    for (int i = 0; i < N; i++) ans1 = max(ans1, dp1[i]);

    int ans2 = 0;
    for (int i = 0; i < N; i++) {
        if (dp1[i] == ans1) {
            ans2 = add(ans2, dp2[i]);
        }
    }

    printf("%d\n", ans1);
    printf("%d\n", ans2);

    return 0;
}
