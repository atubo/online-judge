// https://www.luogu.org/problemnew/show/P3627
// [APIO2009]抢掠计划

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
    vector<vector<int> > bcc;   // component -> all nodes in it
    vector<int> DFN;
    vector<int> Stack;

    vector<int> in, out;        // in and out degrees of the new graph

    TarjanSCC(Graph& g_):g(g_), N(g.N) {
        top = Time = 0;
        taj = 0;
        belong.resize(N, -1);
        DFN.resize(N, -1);
        Stack.resize(N, -1);

        alloc();
    }

    ~TarjanSCC() {
        dealloc();
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
    int *low_;
    bool *instack_;

    void alloc() {
        low_ = new int[N]{};
        memset(low_, 0xFF, N*sizeof(int));
        instack_ = new bool[N]{};
    }

    void dealloc() {
        delete[] low_;
        delete[] instack_;
    }

    void tarjan(int u, int fa) {
        DFN[u] = low_[u] = ++Time;
        Stack[top++] = u;
        instack_[u] = true;

        for (int i = g.head[u]; ~i; i = g.E[i].next) {
            int v = g.E[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low_[u] = min(low_[u], low_[v]);
                if (DFN[u] < low_[v]) {
                    g.E[i].sign = 1;   // it's bridge
                }
            } else if (instack_[v]) low_[u] = min(low_[u], DFN[v]);
        }

        if (low_[u] == DFN[u]) {
            int now;
            bcc.push_back(vector<int>());
            do {
                now = Stack[--top];
                instack_[now] = false;
                belong[now] = taj;
                bcc[taj].push_back(now);
            } while (now != u);
            taj++;
        }
    }
};

void dfs(const TarjanSCC::Graph &g, int u,
         vector<bool> &vis, vector<int> &ret) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!vis[v]) dfs(g, v, vis, ret);
    }
    ret.push_back(u);
}

vector<int> toposort(const TarjanSCC::Graph &g) {
    vector<int> ret;
    vector<bool> vis(g.N, false);
    for (int i = 0; i < g.N; i++) {
        if (!vis[i]) dfs(g, i, vis, ret);
    }
    return ret;
}

const int MAXN = 500010;
int N, M;
int A[MAXN];
int S, P;
bool B[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    TarjanSCC::Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d%d", &S, &P);
    S--;
    for (int i = 0; i < P; i++) {
        int u;
        scanf("%d", &u);
        u--;
        B[u] = true;
    }

    TarjanSCC taj(g);
    taj.dfs();
    auto g2 = taj.build();
    vector<int> cash(taj.taj, 0);
    vector<bool> bar(taj.taj, false);
    for (int i = 0; i < taj.taj; i++) {
        for (int u: taj.bcc[i]) {
            cash[i] += A[u];
            bar[i] = bar[i] || B[u];
        }
    }

    auto topo = toposort(g2);

    vector<int> dp(taj.taj);
    for (int u: topo) {
        for (int eidx = g2.head[u]; ~eidx; eidx = g2.E[eidx].next) {
            int v = g2.E[eidx].to;
            if (!bar[v]) continue;
            bar[u] = true;
            dp[u] = max(dp[u], dp[v]);
        }
        if (bar[u]) dp[u] += cash[u];
    }
    printf("%d\n", dp[taj.belong[S]]);

    return 0;
}
