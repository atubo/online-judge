// https://www.luogu.org/problemnew/show/P3412
// 仓鼠找sugar II

#include <bits/stdc++.h>
using namespace std;

class ModularUtils {
public:
    // return (a * b) mod n, dealing with possible overflow
    static int64_t mul_long(int64_t x, int64_t y, int64_t mod) {
        if (y < 0) {
            x = -x;
            y = -y;
        }
        int64_t s = 0, n = y, t = x;
        while (n) {
            if (n & 1) (s += t) %= mod;
            (t += t) %= mod;
            n >>= 1;
        }
        return s;
    }


    // (g, x, y) that a*x + b*y = g
    static void ext_gcd(int64_t a, int64_t b,
                        int64_t &g, int64_t &x, int64_t &y) {
        if (b == 0) {
            g = a; x = 1; y = 0;
            return;
        }
        int64_t dp, xp, yp;
        ext_gcd(b, a % b, dp, xp, yp);
        g = dp;
        x = yp;
        y = xp - a / b * yp;
    }

    // find x that a*x = b mod n
    static int64_t mod_solve(int64_t a, int64_t b, int64_t n) {
        int64_t d, xp, yp;
        ext_gcd(a, n, d, xp, yp);
        if (b % d == 0) {
            int64_t x0 = (mul_long(xp, b/d, n) + n) % n;
            return x0;
        } else {
            abort();
        }
    }

    static int64_t gcd(int64_t a, int64_t b) {
        if (b == 0) return a;
        return gcd(b, a%b);
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

const int MAXN = 100010;
const int MOD = 998244353;
int sz[MAXN], fa[MAXN];
int64_t ans;

void dfs1(const Graph &g, int u, int f) {
    sz[u] = 1;
    fa[u] = f;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != f) {
            dfs1(g, v, u);
            sz[u] += sz[v];
        }
    }
}

void dfs2(const Graph &g, int u, int f) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != f) {
            ans += 1LL * (2*sz[v]-1) * sz[v] * (sz[0]-sz[v]);
            ans += 1LL * (2*(sz[0]-sz[v])-1) * sz[v] * (sz[0]-sz[v]);
            dfs2(g, v, u);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Graph g(n, 2*(n-1));
    for (int i = 0; i < n-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    dfs1(g, 0, -1);
    dfs2(g, 0, -1);
    printf("%ld\n", ModularUtils::mod_solve(1LL*n*n, ans, MOD));
    return 0;
}
