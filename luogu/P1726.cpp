// https://www.luogu.org/problemnew/show/P1726
// 上白泽慧音

#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
    struct Edge {
        int from, to, nex;
        bool sign;  // bridge?
    };

public:
    class Graph {
    private:
        int N, M;
        vector<int> head;
        vector<Edge> edge;
        int edgenum;
    public:
        Graph(int N_): N(N_) {
            head.resize(N, -1);
            edgenum = 0;
        }

        void add(int u, int v) {
            Edge e = {u, v, head[u], false};
            edge.push_back(e);
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

    vector<vector<int> > ng;    // new graph
    vector<int> du;             // in-degree of the new graph

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

    void assign() {
        // set up new graph
        ng.resize(taj);
        du.resize(taj, 0);
        for (int i = 0; i < g.edgenum; i++) {
            int u = belong[g.edge[i].from], v = belong[g.edge[i].to];
            if (u != v) {
                ng[u].push_back(v);
                du[v]++;
            }
        }
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.edge[i].nex) {
            int v = g.edge[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (DFN[u] < low[v]) {
                    g.edge[i].sign = 1;   // it's bridge
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

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    TarjanSCC::Graph g(N);
    for (int i = 0; i < M; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        a--; b--;
        g.add(a, b);
        if (t == 2) g.add(b, a);
    }
    TarjanSCC tarjan(g);
    tarjan.dfs();

    for (auto &v: tarjan.bcc) {
        sort(v.begin(), v.end());
    }
    vector<int> result;
    for (const auto &v: tarjan.bcc) {
        if (result.size() < v.size() ||
            (result.size() == v.size() && result > v)) {
            result = v;
        }
    }
    printf("%d\n", result.size());
    for (int x: result) {
        printf("%d ", x + 1);
    }
    printf("\n");
    return 0;
}
