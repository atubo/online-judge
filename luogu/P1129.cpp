// https://www.luogu.org/problemnew/show/P1129
// [ZJOI2007]矩阵游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
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
                res += path(i);
            }
        }
        return res;
    }
};

int N;

int main() {
    int T;
    scanf("%d", &T);
    Hungarian hungarian;
    while (T--) {
        scanf("%d", &N);
        hungarian.reset(N, N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int x;
                scanf("%d", &x);
                if (x == 1) {
                    hungarian.addEdge(i, j);
                }
            }
        }
        int m = hungarian.maxMatch();
        printf("%s\n", m == N ? "Yes" : "No");
    }
    return 0;
}
