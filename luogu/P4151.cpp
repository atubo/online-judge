// https://www.luogu.org/problemnew/show/P4151
// [WC2011]最大XOR和路径

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
        int64_t wt;
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
    void addEdge(int u, int v, int64_t w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

class XorLinearBasis {
public:
    int64_t *a;

    XorLinearBasis(int maxl): maxl_(maxl) {
        a = new int64_t[maxl_+1]{};
    }

    ~XorLinearBasis() {
        delete[] a;
    }

    void insert(int64_t t) {
        for (int j = maxl_; j >= 0; j--) {
            if (!(t & (1ll << j))) continue;

            if (a[j]) t ^= a[j];
            else {
                for (int k = 0; k < j; k++) {
                    if (t & (1ll << k)) t ^= a[k];
                }

                for (int k = j+1; k <= maxl_; k++) {
                    if (a[k] & (1ll << j)) a[k] ^= t;
                }
                a[j] = t;
                return;
            }
        }
    }

private:
    int maxl_;
};

const int MAXN = 50010;
int N, M;
bool vis[MAXN];
int64_t D[MAXN];

void dfs(const Graph &g, XorLinearBasis &lb, int u, int64_t d) {
    D[u] = d;
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int64_t w = g.E[eidx].wt;
        if (!vis[v]) {
            dfs(g, lb, v, d^w);
        } else {
            lb.insert(D[u]^D[v]^w);
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int s, t;
        int64_t d;
        scanf("%d%d%lld", &s, &t, &d);
        s--; t--;
        g.addEdge(s, t, d);
        g.addEdge(t, s, d);
    }
    XorLinearBasis lb(60);
    dfs(g, lb, 0, 0ll);

    int64_t ans = D[N-1];
    for (int i = 60; i >= 0; i--) {
        if (((ans >> i) & 1) == 0) {
            ans ^= lb.a[i];
        }
    }
    printf("%lld\n", ans);

    return 0;
}
