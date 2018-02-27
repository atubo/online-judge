// https://www.luogu.org/problemnew/show/P2746
// [USACO5.3]校园网Network of Schools

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
            Edge e = {v, head[u], false};
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

    void assign() {
        // set up new graph
        in.resize(taj, 0);
        out.resize(taj, 0);

        for (int i = 0; i < g.N; i++) {
            for (int eidx = g.head[i]; ~eidx; eidx = g.edge[eidx].next) {
                int u = belong[i];
                int v = belong[g.edge[eidx].to];
                if (u != v) {
                    in[v]++;
                    out[u]++;
                }
            }
        }
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.edge[i].next) {
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

int N;

int main() {
    scanf("%d", &N);
    TarjanSCC::Graph g(N+1);
    for (int i = 1; i <= N; i++) {
        int x;
        while (scanf("%d", &x) == 1 && x > 0) {
            g.add(i, x);
        }
    }
    TarjanSCC tarjan(g);
    tarjan.dfs();
    tarjan.assign();
    int ans1 = 0, ans2 = 0;
    if (tarjan.taj > 2) {
        for (int i = 0; i < tarjan.taj; i++) {
            if (tarjan.in[i] == 0) ans1++;
            if (tarjan.out[i] == 0) ans2++;
        }
        ans1--; ans2--;
    }
    printf("%d\n%d\n", max(ans1, 1), max(ans1, ans2));
    return 0;
}
