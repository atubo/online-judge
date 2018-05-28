// https://www.luogu.org/problemnew/show/P2680
// 运输计划

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300010;
int fe[MAXN], cover[MAXN];
int maxw;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, weight;
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
        E[eidx].weight = w;
        head[u] = eidx++;
    }
};


// Online algorithm, pre-computing O(N log N)
// Each query O(log N)

class BinaryLiftLCA {
    int N_, root_;
    int MAXB_;
    Graph g_;
public:
    vector<int> depth;
    vector<int> dist;
    vector<vector<int> > father;

public:
    BinaryLiftLCA(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, N-1) {
    }

    void addEdge(int u, int v, int w) {
        g_.addEdge(u, v, w);
    }

    void build() {
        depth.resize(N_);
        dist.resize(N_);
        father.resize(N_);
        for (int i = 0; i < N_; i++) {
            father[i].resize(MAXB_, -1);
        }

        dfs(root_, -1, 0, 0);

        binaryLift();
    }

    int findLCA(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        for (int b = MAXB_-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (depth[father[u][b]] >= depth[v]) {
                u = father[u][b];
            }
        }

        if (u == v) return u;

        for (int b = MAXB_-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (father[u][b] != father[v][b]) {
                u = father[u][b];
                v = father[v][b];
            }
        }
        return father[u][0];
    }

private:
    void dfs(int x, int f, int d, int ds) {
        depth[x] = d;
        dist[x] = ds;
        father[x][0] = f;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            int w = g_.E[eidx].weight;
            if (u != f) {
                fe[u] = w;
                dfs(u, x, d+1, ds+w);
            }
        }
    }

    void binaryLift() {
        for (int j = 1; j < MAXB_; j++) {
            for (int i = 0; i < N_; i++) {
                if (father[i][j-1] != -1) {
                    father[i][j] = father[father[i][j-1]][j-1];
                }
            }
        }
    }
};

int N, M;

struct Plan {
    Plan():u(-1), v(-1), w(-1) {}
    Plan(int u_, int v_, int w_): u(u_), v(v_), w(w_) {}
    Plan(const Plan&) = default;
    int u, v, w;
    bool operator < (const Plan &other) const {
        if (w < other.w) return true;
        if (w > other.w) return false;
        if (u < other.u) return true;
        if (u > other.u) return false;
        return (v < other.v);
    }
};

void dfs1(BinaryLiftLCA &lca, const Graph &g, int u, int fa) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].weight;
        if (v != fa) {
            lca.addEdge(u, v, w);
            dfs1(lca, g, v, u);
        }
    }
}

int calcDist(const BinaryLiftLCA &lca, int u, int v) {
    int p = lca.findLCA(u, v);
    return lca.dist[u] + lca.dist[v] - 2 * lca.dist[p];
}

void dfs2(const Graph &g, int u, int fa, int tot, int &ret) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            dfs2(g, v, u, tot, ret);
            cover[u] += cover[v];
        }
    }
    if (cover[u] == tot) ret = max(ret, fe[u]);
}


bool feasible(const Graph &g, const BinaryLiftLCA &lca,
              const vector<Plan> &plan, int x) {
    auto up = lower_bound(plan.begin(), plan.end(), Plan(-1, -1, x+1));
    memset(cover, 0, sizeof(cover));
    int tot = 0;
    for (auto it = up; it != plan.end(); it++) {
        int u = it->u;
        int v = it->v;
        cover[u]++;
        cover[v]++;
        int p = lca.findLCA(u, v);
        cover[p] -= 2;
        tot++;
    }
    int ret = 0;
    dfs2(g, 0, -1, tot, ret);
    return ret >= plan.back().w - x;
}


int solve(const Graph &g, const BinaryLiftLCA &lca, const vector<Plan> &plan) {
    int lo = plan.back().w - maxw - 1, hi = plan.back().w;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(g, lca, plan, mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        a--; b--;
        g.addEdge(a, b, t);
        g.addEdge(b, a, t);
        maxw = max(maxw, t);
    }

    BinaryLiftLCA lca(N, 0);
    dfs1(lca, g, 0, -1);
    lca.build();

    vector<Plan> plan(M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        plan[i] = {u, v, calcDist(lca, u, v)};
    }
    sort(plan.begin(), plan.end());

    printf("%d\n", solve(g, lca, plan));

    return 0;
}
