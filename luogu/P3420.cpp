// https://www.luogu.org/problem/show?pid=3420
// [POI2005]SKA-Piggy Banks

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


// Note: be sure it's DAG
class TopologicalSort {
public:
    int N;
    const vector<vector<int> >& adj;
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = 0; i < (int)adj[v].size(); i++) {
            int m = adj[v][i];
            if (!visited[m]) {
                topologicalSortUtil(m, visited, order);
            }
        }

        order.push(v);
    }

public:
    TopologicalSort(int N_, const vector<vector<int> >& adj_): N(N_), adj(adj_) {
        // initialize N and adj
    }

    void sort() {
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

void dfs(const vector<vector<int> >& g, int u, vector<bool>& visited) {
    visited[u] = true;
    for (int v: g[u]) {
        if (!visited[v]) dfs(g, v, visited);
    }
}

int calcComponent(const vector<vector<int> >& g, int n, const vector<int>& topo) {
    vector<bool> visited(n, false);
    int nc = 0;
    for (int u: topo) {
        if (!visited[u]) {
            dfs(g, u, visited);
            nc++;
        }
    }
    return nc;
}

int main() {
    int N;
    scanf("%d", &N);
    TarjanSCC::Graph g(N);
    for (int i = 0; i < N; i++) {
        int u;
        scanf("%d", &u);
        g.add(u-1, i);
    }

    TarjanSCC tarjan(g);
    tarjan.dfs();
    tarjan.assign();

    TopologicalSort topo(tarjan.taj, tarjan.ng);
    topo.sort();

    printf("%d\n", calcComponent(tarjan.ng, tarjan.taj, topo.topo));
    return 0;
}
