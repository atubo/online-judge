// https://www.luogu.org/problemnew/show/P3275
// [SCOI2011]糖果

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

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


// Note: be sure it's DAG
class TopologicalSort {
public:
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(const Graph &g, int v, bool visited[],
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

    void sort(const Graph &g) {
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
struct Relation {
    int t, a, b;
};

const int MAXN = 100010;
int N, K;
bool vis[MAXN], instack[MAXN];
int candy[MAXN];

bool dfs(const Graph &g, int u) {
    vis[u] = true;
    instack[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (instack[v]) return false;
        if (!vis[v]) {
            if (!dfs(g, v)) return false;
        }
    }
    instack[u] = false;
    return true;
}

int64_t solve(UnionFind &uf, const vector<Relation> &rel,
              const Graph &g) {
    for (int u = 0; u < N; u++) {
        if (!vis[u]) {
            if (!dfs(g, u)) return -1;
        }
    }

    TopologicalSort topo;
    topo.sort(g);

    for (int i = (int)topo.topo.size()-1;  i >= 0; i--) {
        int u = topo.topo[i];
        if (uf.find(u) != u) continue;
        candy[u] = 1;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            candy[u] = max(candy[u], candy[v]+w);
        }
    }

    for (const auto &r: rel) {
        if (r.t == 1) {
            int u = uf.find(r.a);
            int v = uf.find(r.b);
            if (candy[u] < candy[v]) return -1;
        }
    }

    int64_t ans = 0;
    for (int i = 0; i < N; i++) {
        if (uf.find(i) != i) continue;
        ans += 1LL * candy[i] * uf.count(i);
    }

    return ans;
}

Graph buildGraph(UnionFind &uf, const vector<Relation> &rel) {
    TarjanSCC::Graph tg(N);
    for (const auto &r: rel) {
        if (r.t != 1) continue;
        int u = uf.find(r.a), v = uf.find(r.b);
        tg.addEdge(u, v);
    }
    TarjanSCC tarjan(tg);
    tarjan.dfs();
    TarjanSCC::Graph ng = tarjan.build();
    for (int i = 0; i < tarjan.taj; i++) {
        for (int j = 1; j < (int)tarjan.bcc[i].size(); j++) {
            int u = tarjan.bcc[i][j-1];
            int v = tarjan.bcc[i][j];
            uf.join(u, v);
        }
    }

    Graph g(N, K);
    for (int a = 0; a < tarjan.taj; a++) {
        for (int eidx = ng.head[a]; ~eidx; eidx = ng.E[eidx].next) {
            int b = ng.E[eidx].to;
            int u = uf.find(tarjan.bcc[a][0]);
            int v = uf.find(tarjan.bcc[b][0]);
            if (u != v) g.addEdge(u, v, 0);
        }
    }

    for (const auto &r: rel) {
        if (r.t != 0) continue;
        int u = uf.find(r.a), v = uf.find(r.b);
        g.addEdge(u, v, 1);
    }
    return g;
}

int main() {
    scanf("%d%d", &N, &K);
    UnionFind uf(N);
    vector<Relation> rel;
    for (int i = 0; i < K; i++) {
        int x, a, b;
        scanf("%d%d%d", &x, &a, &b);
        a--; b--;
        if (x == 1) uf.join(a, b);
        else if (x == 2) rel.push_back({0, b, a});
        else if (x == 3) rel.push_back({1, a, b});
        else if (x == 4) rel.push_back({0, a, b});
        else rel.push_back({1, b, a});
    }

    auto g = buildGraph(uf, rel);

    auto ans = solve(uf, rel, g);
    printf("%ld\n", ans);

    return 0;
}
