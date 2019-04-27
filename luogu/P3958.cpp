// https://www.luogu.org/problemnew/show/P3958
// 奶酪

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

const int MAXN = 1024;
int T;
int N, H, R;

struct Point {
    int64_t x, y, z;
} P[MAXN];
bool vis[MAXN];

void connect(Graph &g, int u, int v) {
    g.addEdge(u, v);
    g.addEdge(v, u);
}

void dfs(const Graph &g, int u) {
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!vis[v]) dfs(g, v);
    }
}

bool check() {
    Graph g(N+2, (N+2)*(N+2));
    const int bot = N, top = N+1;
    for (int i = 0; i < N; i++) {
        int64_t x = P[i].x;
        int64_t y = P[i].y;
        int64_t z = P[i].z;
        if (z <= R) connect(g, bot, i);
        if (z >= H-R) connect(g, top, i);
        for (int j = i+1; j < N; j++) {
            int64_t x2 = P[j].x;
            int64_t y2 = P[j].y;
            int64_t z2 = P[j].z;
            int64_t d = (x-x2)*(x-x2) + (y-y2)*(y-y2) + (z-z2)*(z-z2);
            if (d <= 4LL*R*R) connect(g, i, j);
        }
    }
    memset(vis, 0, sizeof(vis));
    dfs(g, bot);
    return vis[top];
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &N, &H, &R);
        for (int i = 0; i < N; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            P[i] = {x, y, z};
        }
        int res = check();
        if (res) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
