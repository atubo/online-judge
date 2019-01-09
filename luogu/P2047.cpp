// https://www.luogu.org/problemnew/show/P2047
// [NOI2007]社交网络

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

const int MAXN = 110;
int N, M;
int dist[MAXN][MAXN];
int64_t path[MAXN][MAXN];

void floyd(const Graph &g) {
    memset(dist, 0x3F, sizeof(dist));
    for (int u = 0; u < N; u++) {
        dist[u][u] = 0;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            dist[u][v] = w;
            path[u][v] = 1;
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = 1LL * path[i][k] * path[k][j];
                } else if (dist[i][j] == dist[i][k] + dist[k][j]) {
                    path[i][j] += 1LL * path[i][k] * path[k][j];
                }
            }
        }
    }
}

void solve() {
    for (int v = 0; v < N; v++) {
        double iv = 0;
        for (int s = 0; s < N; s++) {
            if (s == v) continue;
            for (int t = 0; t < N; t++) {
                if (t == v || t == s) continue;
                if (dist[s][v] + dist[v][t] == dist[s][t]) {
                    iv += 1.0*path[s][v]*path[v][t]/path[s][t];
                }
            }
        }
        printf("%.3f\n", iv);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        g.addEdge(a, b, c);
        g.addEdge(b, a, c);
    }
    floyd(g);
    solve();
    return 0;
}
