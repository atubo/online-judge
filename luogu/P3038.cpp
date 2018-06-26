// https://www.luogu.org/problemnew/show/P3038
// [USACO11DEC]牧草种植Grass Planting

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

class BinaryLiftLCA {

    int N_, root_;
    int MAXB_;
    Graph g_;
public:
    vector<int> depth;
    vector<vector<int> > father;

public:
    BinaryLiftLCA(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, N-1) {
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
    }

    void build() {
        depth.resize(N_);
        father.resize(N_);
        for (int i = 0; i < N_; i++) {
            father[i].resize(MAXB_, -1);
        }

        dfs(root_, -1, 0);

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
    void dfs(int x, int f, int d) {
        depth[x] = d;
        father[x][0] = f;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) dfs(u, x, d+1);
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

class BIT {
public:
    // 1-indexed
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

private:
    int64_t* tree;
    const int N;
};

const int MAXN = 100010;
int N, M;
int father[MAXN], dfn[MAXN], last[MAXN];
int currIdx = 1;


void dfs(const Graph &g, BinaryLiftLCA &lca, int u, int fa) {
    dfn[u] = currIdx++;
    father[u] = fa;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            dfs(g, lca, v, u);
            lca.addEdge(u, v);
        }
    }
    last[u] = currIdx - 1;
}

void plant(const BinaryLiftLCA &lca,
           BIT &ft, int x, int y) {
    int p = lca.findLCA(x, y);
    ft.set(dfn[x], 1);
    ft.set(dfn[y], 1);
    ft.set(dfn[p], -2);
}

void query(const BinaryLiftLCA &lca,
           const BIT &ft, int x, int y) {
    if (father[y] == x) swap(x, y);
    int l = dfn[x], r = last[x];
    printf("%lld\n", ft.get(l, r));
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N+1, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    BinaryLiftLCA lca(N+1, 1);
    dfs(g, lca, 1, 0);
    lca.build();

    BIT ft(N);
    char cmd[5];
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%s %d %d", cmd, &x, &y);
        if (cmd[0] == 'P') plant(lca, ft, x, y);
        else query(lca, ft, x, y);
    }

    return 0;
}
