// https://www.luogu.org/problemnew/show/P3308
// [SDOI2014]LIS

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int64_t inf = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int to, next;
        int64_t cap;
    };

    const int N, MAXM;
    int *head;
    Edge *E;
    int e;
private:
    int *curr;

public:
    Dinic(int N_, int M_): N(N_), MAXM(2*M_) {
        alloc();
        reset();
    }

    ~Dinic() {
        dealloc();
    }

    void reset() {
        e = 0;
        memset(head, -1, N * sizeof(int));
    }

    void addEdge(int x, int y, int64_t w, int64_t rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

    int64_t dinic(int s, int t) {
        int64_t ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }

private:
    void alloc() {
        head = new int[N]{};
        curr = new int[N]{};
        E    = new Edge[MAXM]{};
        d    = new int[N]{};
        q    = new int[N]{};
    }

    void dealloc() {
        delete[] head;
        delete[] curr;
        delete[] E;
        delete[] d;
        delete[] q;
    }

    int *d;
    int *q;

    bool bfs(int s, int t) {
        memset(d, -1, N * sizeof(int));
        int front = 0, back = 0;
        q[back++] = t;

        d[t] = 0;
        while (front != back) {
            int u = q[front];
            front++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int64_t low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1 && E[i].cap) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
            // without the following line curr[x] might change
            // prematurely, causing runtime increase
            if (low == ret) break;
        }
        return ret;
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

const int MAXN = 710;
int T;
int N;
int LMAX;
int A[MAXN], B[MAXN], C[MAXN], dp[MAXN], dist[MAXN];
int64_t cost[MAXN];
int attr[MAXN];
bool vis1[2*MAXN], vis2[MAXN];
int top[MAXN], bot[MAXN];

bool compAttr(int u, int v) {
    return C[u] < C[v];
}

bool dfs1(const Dinic &dinic, int u, int t) {
    if (u == t) return true;
    vis1[u] = true;
    for (int eidx = dinic.head[u]; ~eidx; eidx = dinic.E[eidx].next) {
        int c = dinic.E[eidx].cap;
        int v = dinic.E[eidx].to;
        if (c > 0 &&!vis1[v]) {
            if (dfs1(dinic, v, t)) return true;
        }
    }
    return false;
}

void dfs2(const Graph &g, int u) {
    vis2[u] = true;
    dist[u] = dp[u];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (dp[v] == dp[u]-1 && !vis2[v]) dfs2(g, v);
    }
}


int lis() {
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (A[j] < A[i]) dp[i] = max(dp[i], 1+dp[j]);
        }
        ret = max(ret, dp[i]);
    }
    return ret;
}

void solve() {
    memset(dist, 0, sizeof(dist));
    memset(vis1, 0, sizeof(vis1));
    memset(vis2, 0, sizeof(vis2));
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &B[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }

    LMAX = lis();

    Graph g1(N+2, N*(N-1)/2+2*N), g2(N+2, N*(N-1)/2);
    for (int u = 1; u <= N-1; u++) {
        for (int v = u+1; v <= N; v++) {
            if (A[v] > A[u]) {
                g1.addEdge(u, v);
                g2.addEdge(v, u);
            }
        }
    }

    for (int u = 1; u <= N; u++) {
        if (dp[u] == LMAX) dfs2(g2, u);
    }

    Dinic dinic(2*N+2, N*(N-1)/2+3*N);
    const int src = 0, dst = 2*N+1;
    for (int u = 1; u <= N; u++) {
        if (dist[u] == 1) dinic.addEdge(src, top[u], Dinic::inf);
        if (dist[u] == LMAX) dinic.addEdge(bot[u], dst, Dinic::inf);
        dinic.addEdge(top[u], bot[u], B[u]);
        for (int eidx = g1.head[u]; ~eidx; eidx = g1.E[eidx].next) {
            int v = g1.E[eidx].to;
            if (dist[v] == dist[u]+1) {
                dinic.addEdge(bot[u], top[v], Dinic::inf);
            }
        }
    }

    int64_t ans = dinic.dinic(src, dst);
    vector<int> nd(N);
    iota(nd.begin(), nd.end(), 1);
    sort(nd.begin(), nd.end(), compAttr);

    vector<int> pick;
    for (int x: nd) {
        memset(vis1, 0, sizeof(vis1));
        if (!dfs1(dinic, top[x], bot[x])) {
            pick.push_back(x);
            for (int eidx = dinic.head[top[x]]; ~eidx;
                 eidx = dinic.E[eidx].next) {
                int v = dinic.E[eidx].to;
                if (v != bot[x]) continue;
                dinic.E[eidx].cap = 0;
                dinic.E[eidx^1].cap = 0;
                dinic.dinic(dst, bot[x]);
                dinic.dinic(top[x], src);
            }
        }
    }

    sort(pick.begin(), pick.end());
    printf("%ld %d\n", ans, (int)pick.size());
    for (int x: pick) {
        printf("%d ", x);
    }
    printf("\n");
}

void init() {
    for (int i = 1; i < MAXN; i++) {
        top[i] = 2*i-1;
        bot[i] = top[i] + 1;
    }
}

int main() {
    init();
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
