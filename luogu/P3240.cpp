// https://www.luogu.org/problemnew/show/P3240
// [HNOI2015]实验比较

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

const int MOD = 1e9+7;
const int MAXN = 110;
int N, M;
int sz[MAXN], in[MAXN], out[MAXN];
bool vis[MAXN], instack[MAXN];
int binom[MAXN][MAXN];
int fac[MAXN];
int dp[MAXN][MAXN];
int dp2[MAXN][MAXN][MAXN];
int T[MAXN];

struct Rel {
    int x, y;
};

void init() {
    for (int i = 0; i < MAXN; i++) {
        binom[i][0] = 1;
        for (int j = 1; j < i; j++) {
            binom[i][j] = (binom[i-1][j-1] + binom[i-1][j]) % MOD;
        }
        binom[i][i] = 1;
    }

    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = (fac[i-1]*i) % MOD;
    }
}

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

void dfs1(const Graph &g, int u) {
    sz[u] = 1;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        dfs1(g, v);
        sz[u] += sz[v];
    }
}

void merge(int u, int v, int i) {
    for (int j = 0; j < MAXN; j++) {
        for (int k = 0; k <= j; k++) {
            int f = (1LL * binom[j][k] * dp2[u][i-1][k]) % MOD;
            for (int l = j-k; l <= j; l++) {
                dp2[u][i][j] = add(
                    dp2[u][i][j],
                    mul(mul(f, binom[k][l-j+k]), dp[v][l])
                    );
            }
        }
    }
}

void shift(int u, int i) {
    for (int k = MAXN-1; k > 0; k--) {
        dp[u][k] = dp2[u][i][k-1];
    }
}

void dfs2(const Graph &g, int u) {
    dp2[u][0][0] = 1;
    int i = 1;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        dfs2(g, v);
        merge(u, v, i++);
    }

    shift(u, i-1);
}

bool dfs0(const Graph &g, int u) {
    vis[u] = true;
    instack[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (instack[v]) return false;
        if (!vis[v]) {
            bool ok = dfs0(g, v);
            if (!ok) return false;
        }
    }
    instack[u] = false;
    return true;
}

bool check(const Graph &g) {
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            if (!dfs0(g, i)) return false;
        }
    }
    return true;
}

int main() {
    init();
    scanf("%d%d", &N, &M);
    N++;
    UnionFind uf(N);
    vector<Rel> rel;
    for (int i = 0; i < M; i++) {
        int x, y;
        char op[5];
        scanf("%d%s%d", &x, op, &y);
        if (op[0] == '=') uf.join(x, y);
        else rel.push_back({x, y});
    }

    Graph g(N, N);
    for (const auto &r: rel) {
        int x = uf.find(r.x), y = uf.find(r.y);
        g.addEdge(x, y);
        out[x]++;
        in[y]++;
    }

    if (!check(g)) {
        printf("0\n");
        return 0;
    }

    for (int i = 1; i < N; i++) {
        if (uf.find(i) == i && in[i] == 0) {
            g.addEdge(0, i);
        }
    }

    dfs1(g, 0);
    dfs2(g, 0);

    int ans = 0;
    for (int l = 1; l < MAXN; l++) {
        (ans += dp[0][l]) %= MOD;
    }

    printf("%d\n", ans);

    return 0;
}
