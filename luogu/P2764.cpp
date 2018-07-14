// https://www.luogu.org/problemnew/show/P2764
// 最小路径覆盖问题

#include <bits/stdc++.h>
using namespace std;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
    static const int MAXN = 155;
    int nx, ny;
    int g[MAXN][MAXN];

public:
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

int N, M;
bool vis[155];

void dfs(const Hungarian &hungarian, int u) {
    vis[u] = true;
    printf("%d ", u+1);
    int v = hungarian.cx[u];
    if (v != -1) dfs(hungarian, v);
    else printf("\n");
}

void printPath(const Hungarian &hungarian) {
    for (int i = 0; i < N; i++) {
        if (!vis[i]) dfs(hungarian, i);
    }
}


int main() {
    scanf("%d%d", &N, &M);
    Hungarian hungarian;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        hungarian.addEdge(u, v);
    }
    int maxMatch = hungarian.maxMatch();
    printPath(hungarian);
    printf("%d\n", N-maxMatch);
    return 0;
}
