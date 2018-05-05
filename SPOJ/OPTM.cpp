// http://www.spoj.com/problems/OPTM/
// OPTM - Optimal Marks

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

        E = new Edge[2*M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;

        E[eidx].to = u;
        E[eidx].next = head[v];
        head[v] = eidx++;
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

const int MAXN = 510;
int T;
int N, M;
int K;
int mark[MAXN];

int id(int u) {
    return u+1;
}

void dfs(const Dinic &dinic, vector<bool> &visited, int u, int d) {
    visited[u] = true;
    mark[u-1] |= (1 << d);
    for (int eidx = dinic.head[u]; ~eidx; eidx = dinic.E[eidx].next) {
        int cap = dinic.E[eidx].cap;
        int v = dinic.E[eidx].to;
        if (cap > 0 && !visited[v]) {
            dfs(dinic, visited, v, d);
        }
    }
}


void solve(const Graph &g) {
    vector<pair<int, int>> fixed;
    vector<bool> isFixed(N, false);
    for (int i = 0; i < N; i++) {
        if (mark[i] >= 0) {
            fixed.push_back({i, mark[i]});
            isFixed[i] = true;
        } else {
            mark[i] = 0;
        }
    }
    for (int d = 0; d < 31; d++) {
        bool doit = false;
        const int s = 0, t = N+1;
        Dinic dinic(t+1, 2*N+M);
        for (int u = 0; u < N; u++) {
            if (!isFixed[u]) {
                dinic.addEdge(s, id(u), 1);
                dinic.addEdge(id(u), t, 1);
            } else {
                if ((mark[u]>>d) & 1) {
                    doit = true;
                    dinic.addEdge(s, id(u), Dinic::inf);
                } else {
                    dinic.addEdge(id(u), t, Dinic::inf);
                }
            }

            for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
                int v = g.E[eidx].to;
                if (u < v) dinic.addEdge(id(u), id(v), 1, 1);
            }
        }
        if (!doit) continue;
        dinic.dinic(s, t);
        vector<bool> visited(N, false);
        dfs(dinic, visited, s, d);
    }

    for (int i = 0; i < N; i++) {
        printf("%d\n", mark[i]);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        memset(mark, -1, sizeof(mark));
        scanf("%d%d", &N, &M);
        Graph g(N, M);
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            g.addEdge(u, v);
        }
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int u, p;
            scanf("%d%d", &u, &p);
            u--;
            mark[u] = p;
        }

        solve(g);
    }

    return 0;
}
