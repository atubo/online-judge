// https://www.luogu.org/problem/show?pid=1078
// 文化之旅

#include <bits/stdc++.h>
using namespace std;


// Note graph node is 0-indexed
class Graph {
public:
    static const int MAXM = 21000;
    struct Edge {
        int next, to, weight;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].weight = w;
        head[u] = eidx++;
    }
};

const int MAXN = 110;
int N, K, M, S, T;
int C[MAXN];
int A[MAXN][MAXN];
const int inf = 0x3f3f3f3f;
int ans = inf;
bool vis_c[MAXN], vis[MAXN];

void dfs(const Graph &g, int x, int y, int d) {
    if (d > ans) return;
    if (x == y) {
        ans = min(ans, d);
        return;
    }
    for (int ei = g.head[x]; ei != -1; ei = g.E[ei].next) {
        const Graph::Edge &e = g.E[ei];
        int v = e.to;
        int flag = 0;
        for (int j = 0; j < K; j++) {
            if (vis_c[j] && A[j][C[v]]) {
                flag = 1;
                break;
            }
        }
        if (!vis[v] && !vis_c[C[v]] && !flag) {
            vis[v] = vis_c[C[v]] = true;
            dfs(g, v, y, d + e.weight);
            vis[v] = vis_c[C[v]] = false;
        }
    }
}

int main() {
    scanf("%d%d%d%d%d", &N, &K, &M, &S, &T);
    S--; T--;
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
        C[i]--;
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }

    vis[T] = vis_c[C[T]] = true;
    dfs(g, T, S, 0);
    printf("%d\n", ans == inf ? -1 : ans);
    return 0;
}
