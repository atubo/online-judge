// https://www.luogu.org/problemnew/show/P2754
// [CTSC1999]家园

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

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
    struct Edge {
        int to, next, cap;
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

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

    int dinic(int s, int t) {
        int ans = 0;
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

    int dfs(int x, int low, int t) {
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

const int MAXM = 22;
struct Routes {
    int h, r;
    int s[15];
} routes[MAXM];

int N, M, K;
bool vis[15];

bool dfs(const Graph &g, int u) {
    vis[u] = true;
    if (u == N+1) return true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!vis[v]) {
            if (dfs(g, v)) return true;
        }
    }
    return false;
}

bool reachable() {
    Graph g(N+2, M*15);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < routes[i].r; j++) {
            int k = (j+1) % routes[i].r;
            g.addEdge(routes[i].s[j], routes[i].s[k]);
        }
    }
    return dfs(g, 0);
}

int id(int t, int i) {
    return t * (N+2) + i + 1;
}

bool check(int tmax) {
    Dinic dinic((tmax+1)*(N+2)+1, (N+2)*tmax + M*tmax + 1);

    dinic.addEdge(0, 1, K);
    for (int t = 0; t < tmax; t++) {
        for (int i = 0; i < N+2; i++) {
            dinic.addEdge(id(t, i), id(t+1, i), Dinic::inf);
        }
        for (int i = 0; i < M; i++) {
            int h = routes[i].h;
            int r = routes[i].r;
            dinic.addEdge(id(t, routes[i].s[t%r]),
                          id(t+1, routes[i].s[(t+1)%r]),
                          h);
        }
    }

    return dinic.dinic(0, id(tmax, N+1)) == K;
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 0; i < M; i++) {
        int h, r;
        scanf("%d%d", &h, &r);
        routes[i].h = h;
        routes[i].r = r;
        for (int j = 0; j < r; j++) {
            int s;
            scanf("%d", &s);
            if (s == -1) s = N+1;
            routes[i].s[j] = s;
        }
    }
    if (!reachable()) {
        printf("0\n");
        return 0;
    }

    int lo = 0, hi = (N+2)*(N+2)*K;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);
    return 0;
}
