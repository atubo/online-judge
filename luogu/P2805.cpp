// https://www.luogu.org/problemnew/show/P2805
// [NOI2009]植物大战僵尸

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 32;
bool added[MAXN*MAXN][MAXN*MAXN];

class TarjanSCC {
    struct Edge {
        int to, next;
        bool sign;  // bridge?
    };

public:
    class Graph {
    private:
        int edgenum;
    public:
        const int N;
        vector<int> head;
        vector<Edge> E;
    public:
        Graph(int N_): N(N_) {
            head.resize(N, -1);
            edgenum = 0;
        }

        void addEdge(int u, int v) {
            Edge e = {v, head[u], false};
            E.push_back(e);
            head[u] = edgenum++;
        }
        friend class TarjanSCC;
    };

public:
    Graph& g;
    const int N;
    int taj, top, Time;    // SCC index
    vector<int> belong; // node -> its component
    vector<bool> instack;
    vector<vector<int> > bcc;   // component -> all nodes in it
    vector<int> DFN;
    vector<int> low;
    vector<int> Stack;

    vector<int> in, out;        // in and out degrees of the new graph

    TarjanSCC(Graph& g_):g(g_), N(g.N) {
        top = Time = 0;
        taj = 0;
        belong.resize(N, -1);
        instack.resize(N, false);
        DFN.resize(N, -1);
        low.resize(N, -1);
        Stack.resize(N, -1);
    }

    void dfs() {
        for (int i = 0; i < N; i++) {
            if (DFN[i] == -1) tarjan(i, i);
        }
    }

    Graph build() {
        // set up new graph
        Graph ng(taj);
        in.resize(taj, 0);
        out.resize(taj, 0);

        for (int i = 0; i < g.N; i++) {
            for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
                int u = belong[i];
                int v = belong[g.E[eidx].to];
                if (u != v && !added[u][v]) {
                    ng.addEdge(u, v);
                    out[u]++;
                    in[v]++;
                    added[u][v] = true;
                }
            }
        }
        return ng;
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.E[i].next) {
            int v = g.E[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (DFN[u] < low[v]) {
                    g.E[i].sign = 1;   // it's bridge
                }
            } else if (instack[v]) low[u] = min(low[u], DFN[v]);
        }

        if (low[u] == DFN[u]) {
            int now;
            bcc.push_back(vector<int>());
            do {
                now = Stack[--top];
                instack[now] = false;
                belong[now] = taj;
                bcc[taj].push_back(now);
            } while (now != u);
            taj++;
        }
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

int N, M;
int score[MAXN][MAXN];
bool locked[MAXN*MAXN];
int tot;

int id(int i, int j) {
    return i*(M+1) + j;
}

void markLocked(TarjanSCC &tarjan, const TarjanSCC::Graph &g) {
    queue<int> q;
    for (int i = 0; i < g.N; i++) {
        if (tarjan.in[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (tarjan.bcc[u].size() > 1) locked[u] = true;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (--tarjan.in[v] == 0) q.push(v);
            if (locked[u]) locked[v] = true;
        }
    }
}


int main() {
    scanf("%d%d", &N, &M);
    TarjanSCC::Graph g1(N*M+N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            g1.addEdge(id(i, j+1), id(i, j));
            scanf("%d", &score[i][j]);
            int w;
            scanf("%d", &w);
            for (int k = 0; k < w; k++) {
                int r, c;
                scanf("%d%d", &r, &c);
                g1.addEdge(id(i, j), id(r, c));
            }
        }
    }
    TarjanSCC tarjan(g1);
    tarjan.dfs();
    TarjanSCC::Graph g2 = tarjan.build();
    markLocked(tarjan, g2);

    const int src = 0, dst = tarjan.taj + 1;
    Dinic dinic(dst+1, 2*tarjan.taj + tarjan.taj*tarjan.taj);
    for (int i = 0; i < tarjan.taj; i++) {
        if (!locked[i]) {
            int r = tarjan.bcc[i][0] / (M+1);
            int c = tarjan.bcc[i][0] % (M+1);
            tot += max(0, score[r][c]);
            if (score[r][c] > 0) {
                dinic.addEdge(src, i+1, score[r][c]);
            }
            if (score[r][c] < 0) {
                dinic.addEdge(i+1, dst, -score[r][c]);
            }
            for (int eidx = g2.head[i]; ~eidx; eidx = g2.E[eidx].next) {
                int v = g2.E[eidx].to;
                if (!locked[v]) {
                    dinic.addEdge(v+1, i+1, Dinic::inf);
                }
            }
        }
    }

    int f = dinic.dinic(src, dst);
    printf("%d\n", tot - f);

    return 0;
}
