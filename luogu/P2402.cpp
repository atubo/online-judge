// https://www.luogu.org/problemnew/show/P2402
// 奶牛隐藏

#include <bits/stdc++.h>
using namespace std;

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
            int64_t k = dfs(s, inf, t);
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

    int64_t dfs(int x, int64_t low, int t) {
        if (x == t || !low) return low;
        int64_t ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1 && E[i].cap) {
                int64_t k = dfs(v, min(low-ret, E[i].cap), t);
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

const int MAXN = 210;
int N, M;
int S[MAXN], P[MAXN];
int64_t D[MAXN][MAXN];
int64_t MAXD;
int64_t TOTS;
const int64_t INF = 0x3f3f3f3f3f3f3f3f;

void floyd(const Graph &g) {
    memset(D, 0x3F, sizeof(D));
    MAXD = 0;
    for (int u = 0; u < N; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            D[u][v] = min(D[u][v], (int64_t)w);
        }
        D[u][u] = 0;
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (D[i][j] != INF) {
                MAXD = max(MAXD, D[i][j]);
            }
        }
    }
}

bool check(int64_t maxd) {
    Dinic dinic(2*N+2, N*N+2*N);
    const int src = 0, dst = 2*N+1;
    for (int i = 0; i < N; i++) {
        dinic.addEdge(src, i+1, S[i]);
        dinic.addEdge(N+1+i, dst, P[i]);
        for (int j = 0; j < N; j++) {
            if (D[i][j] <= maxd) {
                dinic.addEdge(i+1, N+1+j, Dinic::inf);
            }
        }
    }
    int64_t flow = dinic.dinic(src, dst);
    return flow == TOTS;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &S[i], &P[i]);
        TOTS += S[i];
    }
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        g.addEdge(a, b, c);
        g.addEdge(b, a, c);
    }
    floyd(g);

    if (!check(MAXD)) {
        printf("-1\n");
        return 0;
    }

    int64_t lo = -1, hi = MAXD;
    while (lo < hi - 1) {
        int64_t mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%ld\n", hi);
    return 0;
}
