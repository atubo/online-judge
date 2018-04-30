// https://www.luogu.org/problemnew/show/P2319
// [HNOI2006]超级英雄

#include <bits/stdc++.h>
using namespace std;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
public:
    static const int MAXN = 1010;
    int nx, ny;
    int g[MAXN][MAXN];

    int cx[MAXN], cy[MAXN];
    int mk[MAXN];

    int path(int u) {
        for (int v = 0; v < ny; v++) {
            if (g[u][v] && !mk[v]) {
                mk[v] = 1;
                if (cy[v] == -1 || path(cy[v])) {
                    cx[u] = v;
                    cy[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

public:
    Hungarian() {
        reset(MAXN-1, MAXN-1);
    }

    void reset(int nx_, int ny_) {
        nx = nx_;
        ny = ny_;
        memset(g, 0, sizeof(g));
    }

    void addEdge(int x, int y) {
        g[x][y] = 1;
    }

    int maxMatch() {
        int res = 0;
        memset(cx, -1, sizeof(cx));
        memset(cy, -1, sizeof(cy));
        for (int i = 0; i < nx; i++) {
            if (cx[i] == -1) {
                memset(mk, 0, sizeof(mk));
                int d = path(i);
                res += d;
                if (!d) break;
            }
        }
        return res;
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    Hungarian hungarian;
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        hungarian.addEdge(i, x);
        hungarian.addEdge(i, y);
    }
    int ans = hungarian.maxMatch();
    printf("%d\n", ans);
    for (int i = 0; i < ans; i++) {
        printf("%d\n", hungarian.cx[i]);
    }

    return 0;
}
