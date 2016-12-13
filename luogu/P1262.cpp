// https://www.luogu.org/problem/show?pid=1262
// 间谍网络
#include <limits.h>
#include <cstdio>
#include <vector>
using namespace std;

class TarjanSCC {
    struct Edge {
        int from, to, nex;
        bool sign;  // bridge?
    };

public:
    class Graph {
    public:
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

void dfs(const TarjanSCC::Graph& g, int u, vector<bool>& visited) {
    visited[u] = true;
    for (int i = g.head[u]; ~i; i = g.edge[i].nex) {
        int v = g.edge[i].to;
        if (!visited[v]) {
            dfs(g, v, visited);
        }
    }
}

int main() {
    int N, P;
    scanf("%d", &N);
    scanf("%d", &P);
    vector<int> fund(N, INT_MAX);
    int a, b;
    for (int i = 0; i < P; i++) {
        scanf("%d %d", &a, &b);
        fund[a-1] = b;
    }
    TarjanSCC::Graph g(N);
    int R;
    scanf("%d", &R);
    while (R--) {
        scanf("%d %d", &a, &b);
        a--; b--;
        g.add(a, b);
    }

    TarjanSCC tarjan(g);
    tarjan.dfs();
    tarjan.assign();

    int total = 0;
    bool feasible = true;
    for (int i = 0; i < tarjan.taj; i++) {
        if (tarjan.du[i] > 0) continue;
        int f = INT_MAX;
        for (int j = 0; j < (int)tarjan.bcc[i].size(); j++) {
            int u = tarjan.bcc[i][j];
            f = min(f, fund[u]);
        }
        if (f == INT_MAX) {
            feasible = false;
            break;
        } else {
            total += f;
        }
    }

    if (feasible) {
        printf("YES\n%d\n", total);
    } else {
        vector<bool> visited(N, false);
        for (int i = 0; i < N; i++) {
            if (!visited[i] && fund[i] < INT_MAX) {
                dfs(g, i, visited);
            }
        }
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                printf("NO\n%d\n", i+1);
                break;
            }
        }
    }
    return 0;
}
