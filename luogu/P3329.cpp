// https://www.luogu.org/problemnew/show/P3329
// [ZJOI2011]最小割

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
    struct Edge {
        int to, next, cap;
    };

    const int N;
    int *head;
    Edge *E;
    int e;
private:
    static const int MAXM = 10000;
    int *curr;

public:
    Dinic(int N_): N(N_) {
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
            if (d[v] == d[x] - 1) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
        }
        return ret;
    }
};

class GomoryHuTree {
private:
    int N;
    Dinic dinic;
    int *vis;
    int *id;
    int currCompId;
public:
    vector<vector<pair<int, int64_t>>> edges;

    GomoryHuTree(int N_): N(N_), dinic(N_), currCompId(0) {
        alloc();
    }

    ~GomoryHuTree() {
        dealloc();
    }

    void addEdge(int u, int v, int w) {
        dinic.addEdge(u, v, w, w);
    }

    void build(int l, int r) {
        if (l >= r) return;
        vector<int> tmp(N);

        const int S = id[l], T = id[l+1];
        resetFlow();
        int64_t V = dinic.dinic(S, T);
        currCompId++;
        dfs(S);
        int p = l, q = r;
        for (int i = l; i <= r; i++) {
            if (vis[id[i]] == currCompId) tmp[p++] = id[i];
            else tmp[q--] = id[i];
        }
        edges[S].push_back(make_pair(T, V));
        edges[T].push_back(make_pair(S, V));
        for (int i = l; i <= r; i++) id[i] = tmp[i];
        build(l, p - 1);
        build(q + 1, r);
    }

private:
    void alloc() {
        vis = new int[N];
        memset(vis, -1, N * sizeof(int));
        id  = new int[N];
        for (int i = 0; i < N; i++) {
            id[i] = i;
        }
        edges.resize(N);
    }

    void dealloc() {
        delete[] vis;
    }

    void dfs(int x) {
        vis[x] = currCompId;
        for (int eidx = dinic.head[x]; ~eidx; eidx = dinic.E[eidx].next) {
            int v = dinic.E[eidx].to;
            int c = dinic.E[eidx].cap;
            if (c && vis[v] != currCompId) {
                dfs(v);
            }
        }
    }

    void resetFlow() {
        for (int e = 0; e < dinic.e; e += 2) {
            int c1 = dinic.E[e].cap;
            int c2 = dinic.E[e^1].cap;
            int c = (c1 + c2) / 2;
            dinic.E[e].cap = dinic.E[e^1].cap = c;
        }
    }
};

const int MAXN = 150;
int dist[MAXN][MAXN];

void travel(int start, int u, int fa, int64_t flow, const GomoryHuTree &ct) {
    for (const auto &p: ct.edges[u]) {
        int v = p.first;
        int64_t f = min(flow, p.second);
        if (v != fa) {
            dist[start][v] = f;
            travel(start, v, u, f, ct);
        }
    }
}

int main() {
    int nt;
    scanf("%d", &nt);
    while(nt--) {
        int N, M;
        scanf("%d%d", &N, &M);
        GomoryHuTree ct(N);
        for (int i = 0; i < M; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            u--; v--;
            if (u == v) continue;
            ct.addEdge(u, v, c);
        }
        ct.build(0, N-1);
        memset(dist, 0, sizeof(dist));
        for (int u = 0; u < N; u++) {
            travel(u, u, -1, INT_MAX, ct);
        }
        int Q;
        scanf("%d", &Q);
        while (Q--) {
            int x;
            scanf("%d", &x);
            int ans = 0;
            for (int u = 0; u < N-1; u++) {
                for (int v = u+1; v < N; v++) {
                    if (dist[u][v] <= x) ans++;
                }
            }
            printf("%d\n", ans);
        }
        printf("\n");
    }
    return 0;
}
