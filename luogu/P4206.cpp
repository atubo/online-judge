// https://www.luogu.org/problemnew/show/P4206
// [NOI2005]聪聪与可可

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

const int MAXN = 1005;
int N, E;
int C, M;
double dp[MAXN][MAXN];
int D[MAXN][MAXN];
int P[MAXN][MAXN];

void bfs(const Graph &g, int s) {
    queue<int> q;
    q.push(s);
    D[s][s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (D[s][v] == -1 || (D[s][v] == D[s][u]+1 && u < P[s][v])) {
                if (D[s][v] == -1) q.push(v);
                D[s][v] = D[s][u] + 1;
                P[s][v] = u;
            }
        }
    }
};

double solve(const Graph &g, int u, int v) {
    if (D[u][v] <= 2) {
        return dp[u][v] = (D[u][v] != 0);
    }

    if (dp[u][v] >= 0) return dp[u][v];

    double &ret = dp[u][v] = 1;

    u = P[v][u];
    u = P[v][u];

    double t = solve(g, u, v);
    int cnt = 1;
    for (int eidx = g.head[v]; ~eidx; eidx = g.E[eidx].next) {
        int w = g.E[eidx].to;
        t += solve(g, u, w);
        cnt++;
    }
    ret += t/cnt;
    return ret;
}

int main() {
    memset(D, -1, sizeof(D));
    memset(P, -1, sizeof(P));
    scanf("%d%d", &N, &E);
    Graph g(N, 2*E);
    scanf("%d%d", &C, &M);
    C--; M--;
    for (int i = 0; i < E; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }

    for (int s = 0; s < N; s++) {
        bfs(g, s);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }

    double ans = solve(g, C, M);
    printf("%.3f\n", ans);
    return 0;
}
