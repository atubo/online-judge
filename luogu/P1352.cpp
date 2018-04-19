// https://www.luogu.org/problemnew/show/P1352
// 没有上司的舞会

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 6010;
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N;

    Edge *E;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[MAXM]{};
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

const int MAXN = 6010;
int N;
int R[MAXN], father[MAXN];
int dp[MAXN][2];

int dfs(const Graph &g, int u, bool sel) {
    if (dp[u][sel] != INT_MIN) return dp[u][sel];
    int &ret = dp[u][sel] = 0;
    if (sel) {
        ret += R[u];
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            ret += dfs(g, v, false);
        }
    } else {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            ret += max(dfs(g, v, true), dfs(g, v, false));
        }
    }
    return ret;
}

int main() {
    memset(father, -1, sizeof(father));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &R[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = INT_MIN;
        }
    }
    Graph g(N);
    for (int i = 0; i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        father[x] = y;
        g.addEdge(y, x);
    }
    int root = -1;
    for (int i = 0; i < N; i++) {
        if (father[i] == -1) {
            root = i;
            break;
        }
    }
    int ans = max(dfs(g, root, 0), dfs(g, root, 1));
    printf("%d", ans);
    return 0;
}
