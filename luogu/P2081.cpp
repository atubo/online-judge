// https://www.luogu.org/problem/P2081
// [NOI2012]迷失游乐园

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

const int MAXN = 100010;
const int MAXL = 25;
int N, M;
int NC[MAXN];
int FA[MAXN], NB[2][MAXN], LI[MAXN];
int D2F[MAXN];
double D1[MAXN], D2[MAXN], WT[2][MAXN];
bool vis[MAXN];
vector<int> RNG;
double dp[MAXL][MAXL][2];

void dfs1(const Graph &g, int u, int fa) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            dfs1(g, v, u);
            D1[u] += (w + D1[v]);
            NC[u]++;
        }
    }
    if (NC[u]) D1[u] /= NC[u];
}

void dfs2(const Graph &g, int u, int v, int w, bool root) {
    const int m = NC[v];
    if (root) {
        if (m > 1) D2[u] = w + (m*D1[v] - (w+D1[u]))/(m-1);
        else D2[u] = w;
    } else {
        D2[u] = w + (m*D1[v] - w - D1[u] + D2[v])/m;
    }

    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int x = g.E[eidx].to;
        int y = g.E[eidx].wt;
        if (x != v) {
            dfs2(g, x, u, y, false);
        }
    }
}

void solve1(const Graph &g) {
    dfs1(g, 0, -1);
    for (int eidx = g.head[0]; ~eidx; eidx = g.E[eidx].next) {
        int u = g.E[eidx].to;
        int w = g.E[eidx].wt;
        dfs2(g, u, 0, w, true);
    }
    double ans = 0;
    for (int i = 0; i < N; i++) {
        const int m = NC[i];
        double d = (i > 0 ? m*D1[i]/(m+1) + D2[i]/(m+1): D1[i]);
        ans += d;
    }
    ans /= N;
    printf("%.5f", ans);
}

void traverse(const Graph &g, int u, int v) {
    int x = u, last = v;
    while (x != v) {
        NB[0][x] = FA[x];
        NB[1][x] = last;
        LI[x] = RNG.size();
        RNG.push_back(x);
        WT[0][x] = D2F[x];
        WT[1][x] = D2F[last];
        last = x;
        x = FA[x];
    }
    NB[0][x] = u;
    NB[1][x] = last;
    LI[x] = RNG.size();
    RNG.push_back(x);
    WT[0][x] = D2F[x];
    WT[1][x] = D2F[last];
}

bool dfs3(const Graph &g, int u, int fa) {
    FA[u] = fa;
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            D2F[v] = w;
            if (vis[v]) {
                traverse(g, u, v);
                return true;
            }
            if (dfs3(g, v, u)) return true;
        }
    }
    return false;
}

void dfs4(const Graph &g, int u, int fa) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa && v != NB[0][u] && v != NB[1][u]) {
            dfs4(g, v, u);
            D1[u] += (w + D1[v]);
            NC[u]++;
        }
    }
    if (NC[u]) D1[u] /= NC[u];
}

double solve(const Graph &g, int u, int d, int s) {
    int ui = LI[u], si = LI[s];
    if (dp[ui][si][d] >= 0) return dp[ui][si][d];
    int v = NB[d][u];
    double &ret = dp[ui][si][d];
    const int m = NC[v];
    if (NB[d][v] != s) {
        ret = WT[d][u] + m*D1[v]/(m+1) + solve(g, v, d, s)/(m+1);
    } else {
        ret = WT[d][u] + D1[v];
    }
    return ret;
}

void solveLoop(const Graph &g) {
    const int n = RNG.size();
    for (int i = 0; i < n; i++) {
        int s = RNG[i];
        for (int j = 0; j < n; j++) {
            int u = RNG[(i+j)%n];
            solve(g, u, 0, s);
            solve(g, u, 1, s);
        }
    }
}

void dfs5(const Graph &g, int u, int fa, int wf, int mf) {
    const int m = NC[u];
    if (fa == -1) {
        D2[u] = (m*D1[u] + solve(g, u, 0, u) + solve(g, u, 1, u))/(m + 2);
    } else {
        D2[u] = (m*D1[u] + wf + (D2[fa]*mf-wf-D1[u])/(mf-1))/(m + 1);
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa && v != NB[0][u] && v != NB[1][u]) {
            dfs5(g, v, u, w, m+1+(fa==-1));
        }
    }
}

void solve2(const Graph &g) {
    dfs3(g, N-1, -1);
    for (int u: RNG) {
        dfs4(g, u, -1);
    }
    solveLoop(g);
    for (int s: RNG) {
        dfs5(g, s, -1, 0, 0);
    }
    double ans = 0;
    for (int i = 0; i < N; i++) {
        ans += D2[i];
    }
    printf("%.5f", ans/N);
}

int main() {
    memset(NB, -1, sizeof(NB));
    for (int i = 0; i < MAXL; i++) {
        for (int j = 0; j < MAXL; j++) {
            for (int d = 0; d < 2; d++) {
                dp[i][j][d] = -1;
            }
        }
    }
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        x--; y--;
        g.addEdge(x, y, w);
        g.addEdge(y, x, w);
    }

    if (M == N-1) {
        solve1(g);
    } else {
        solve2(g);
    }
    return 0;
}
