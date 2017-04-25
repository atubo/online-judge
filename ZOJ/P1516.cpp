// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1516
// Uncle Tom's Inherited Land

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int pond[MAXN][MAXN];
int N, M, K;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
    static const int MAXN = 55;
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

bool inRange(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}

const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};

int main() {
    Hungarian hungarian;
    while (scanf("%d%d", &N, &M) && (N != 0 || M != 0)) {
        memset(pond, 0, sizeof(pond));
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--; y--;
            pond[x][y] = -1;
        }
        int nx = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((i + j) % 2 == 0 && pond[i][j] != -1) {
                    pond[i][j] = nx++;
                }
            }
        }

        int ny = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((i +j) % 2 == 1 && pond[i][j] != -1) {
                    pond[i][j] = ny++;
                }
            }
        }

        hungarian.reset(nx, ny);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((i + j) % 2 == 0 && pond[i][j] != -1) {
                    for (int d = 0; d < 4; d++) {
                        int p = i + DX[d];
                        int q = j + DY[d];
                        if (inRange(p, q) && pond[p][q] != -1) {
                            hungarian.addEdge(pond[i][j], pond[p][q]);
                        }
                    }
                }
            }
        }

        printf("%d\n", hungarian.maxMatch());
    }
    return 0;
}
