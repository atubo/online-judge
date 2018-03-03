// https://www.luogu.org/problemnew/show/P2403
// [SDOI2010]所驼门王的宝藏

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

    void link(int u, int v) {
        if (u == v) return;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
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

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

class TarjanSCC {
    struct Edge {
        int to, next;
        bool sign;  // bridge?
    };

public:
    class Graph {
    public:
        int N, M;
        vector<int> head;
        vector<Edge> E;
        int edgenum;
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

    vector<vector<int> > ng;    // new graph
    vector<int> in, out;        // in and out degrees of the new graph
    vector<int> wt;

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

    void assign(UnionFind &uf) {
        // set up new graph
        ng.resize(taj);
        in.resize(taj, 0);
        out.resize(taj, 0);
        wt.resize(taj, 0);

        for (int i = 0; i < taj; i++) {
            for (int u: bcc[i]) {
                wt[i] += uf.count(u);
            }
        }

        for (int i = 0; i < g.N; i++) {
            for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
                int u = belong[i];
                int v = belong[g.E[eidx].to];
                if (u != v) {
                    ng[u].push_back(v);
                    out[u]++;
                    in[v]++;
                }
            }
        }
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

const int MAXN = 100010;

struct Portal {
    int x, y, t, id;
} portals[MAXN];

int N, R, C;

using PortalLines = unordered_map<int, vector<Portal>>;
using LineLeaders = unordered_map<int, int>;
PortalLines rows, cols;
LineLeaders rowLeader, colLeader;

void process(UnionFind &uf, const PortalLines &line,
             int type, LineLeaders &leader) {
    for (const auto &p: line) {
        int last = -1;
        for (const auto &pt: p.second) {
            if (pt.t == type) {
               if (last != -1) {
                  uf.join(last, pt.id);
               }
               last = pt.id;
            }
        }
        if (last != -1){
            leader[p.first] = uf.find(last);
        }
    }
}

void connect(TarjanSCC::Graph &g, int u) {
    int x = portals[u].x, y = portals[u].y;
    for (int xp = max(0, x-1); xp <= min(R-1, x+1); xp++) {
        if (rows.count(xp) == 0) continue;
        const auto &line = rows.at(xp);
        auto it1 = lower_bound(line.begin(), line.end(),
                               Portal{xp, y-1, -1, -1},
                               [](const Portal &p1, const Portal &p2) {
                               return p1.y < p2.y;
                               });
        auto it2 = upper_bound(line.begin(), line.end(),
                               Portal{xp, y+1, -1, -1},
                               [](const Portal &p1, const Portal &p2) {
                               return p1.y < p2.y;
                               });
        for (auto it = it1; it != it2; it++) {
            const Portal &pt = *it;
            int v = pt.id;
            if (u == v) continue;
            if (pt.t == 1) {
                v = rowLeader.at(xp);
            } else if (pt.t == 2) {
                v = colLeader.at(pt.y);
            }
            g.addEdge(u, v);
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &R, &C);
    for (int i = 0; i < N; i++) {
        int x, y, t;
        scanf("%d%d%d", &x, &y, &t);
        x--; y--;
        portals[i] = {x, y, t, i};
    }
    for (int i = 0; i < N; i++) {
        const auto &p = portals[i];
        cols[p.y].push_back(p);
        rows[p.x].push_back(p);
    }

    for (auto &p: rows) {
        sort(p.second.begin(), p.second.end(),
             [](const Portal &p1, const Portal &p2) {
             return p1.y < p2.y;
             });
    }
    for (auto &p: cols) {
        sort(p.second.begin(), p.second.end(),
             [](const Portal &p1, const Portal &p2) {
             return p1.x < p2.x;
             });
    }

    UnionFind uf(N);
    TarjanSCC::Graph g(N);
    process(uf, rows, 1, rowLeader);
    process(uf, cols, 2, colLeader);

    for (const auto &p: rows) {
        if (rowLeader.count(p.first) == 0) continue;
        int u = rowLeader[p.first];
        for (const auto &pt: p.second) {
            if (pt.t == 2) {
                int v = colLeader.at(pt.y);
                g.addEdge(u, v);
            } else if (pt.t == 3) {
                g.addEdge(u, pt.id);
            }
        }
    }

    for (const auto &p: cols) {
        if (colLeader.count(p.first) == 0) continue;
        int u = colLeader[p.first];
        for (const auto &pt: p.second) {
            if (pt.t == 1) {
                int v = rowLeader.at(pt.x);
                g.addEdge(u, v);
            } else if (pt.t == 3) {
                g.addEdge(u, pt.id);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (portals[i].t == 3) {
            connect(g, i);
        }
    }

    TarjanSCC tarjan(g);
    tarjan.dfs();
    tarjan.assign(uf);

    // topo sort
    queue<int> qu;
    for (int i = 0; i < tarjan.taj; i++) {
        if (tarjan.in[i] == 0) {
            qu.push(i);
        }
    }
    vector<int> topo;
    while (!qu.empty()) {
        int u = qu.front();
        topo.push_back(u);
        qu.pop();
        for (int v: tarjan.ng[u]) {
            tarjan.in[v]--;
            if (tarjan.in[v] == 0) {
                qu.push(v);
            }
        }
    }
    int ans = 0;
    vector<int> dp(tarjan.taj, 0);
    for (int i = tarjan.taj-1; i >= 0; i--) {
        int u = topo[i];
        int next = 0;
        for (int v: tarjan.ng[u]) {
            next = max(next, dp[v]);
        }
        dp[u] = tarjan.wt[u] + next;
        ans = max(ans, dp[u]);
    }
    printf("%d\n", ans);

    return 0;
}
