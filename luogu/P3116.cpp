// https://www.luogu.org/problemnew/show/P3116
// [USACO15JAN]约会时间Meeting Time

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt1, wt2;
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
    void addEdge(int u, int v, int w1, int w2) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt1 = w1;
        E[eidx].wt2 = w2;
        head[u] = eidx++;
    }
};

int N, M;
bool D1[100][10001], D2[100][10001];

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, M);
    for (int i = 0; i < M; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a--; b--;
        g.addEdge(a, b, c, d);
    }
    D1[0][0] = D2[0][0] = true;
    for (int u = 0; u < N; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w1 = g.E[eidx].wt1;
            int w2 = g.E[eidx].wt2;
            for (int i = 0; i <= 10000; i++) {
                if (D1[u][i]) D1[v][i+w1] = true;
            }
            for (int i = 0; i <= 10000; i++) {
                if (D2[u][i]) D2[v][i+w2] = true;
            }
        }
    }
    int ans = -1;
    for (int i = 0; i <= 10000; i++) {
        if (D1[N-1][i] && D2[N-1][i]) {
            ans = i;
            break;
        }
    }
    if (ans != -1) {
        printf("%d\n", ans);
    } else {
        printf("IMPOSSIBLE\n");
    }
        
    return 0;
}
