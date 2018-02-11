// https://www.luogu.org/problemnew/show/P1351
// 联合权值

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 400010;
public:
    struct Edge {
        int next, to;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 200010;
const int MOD = 10007;
int N;
int W[MAXN], tot[MAXN], mx[MAXN];

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int dfs_max(const Graph &g, int u, int fa) {
    int ret = 0;
    vector<int> cw;
    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            ret = max(ret, dfs_max(g, v, u));
            ret = max(ret, mx[v] * W[u]);
            cw.push_back(W[v]);
            mx[u] = max(mx[u], W[v]);
        }
    }
    if (cw.size() >= 2) {
        sort(cw.begin(), cw.end(), greater<int>());
        ret = max(ret, cw[0] * cw[1]);
    }
    return ret;
}

int dfs_sum(const Graph &g, int u, int fa) {
    int ret = 0;
    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            ret = add(ret, dfs_sum(g, v, u));
            ret = add(ret, mul(mul(tot[v], W[u]), 2));
            tot[u] += W[v];
        }
    }
    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
        int v  = g.E[eidx].to;
        if (v != fa) {
            ret = add(ret, mul(W[v], tot[u] - W[v]));
        }
    }
    return ret;
}


int main() {
    scanf("%d", &N);
    Graph g(N+1);
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &W[i]);
    }
    printf("%d %d", dfs_max(g, 1, 0), dfs_sum(g, 1, 0));
    return 0;
}
