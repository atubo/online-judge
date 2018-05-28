// https://www.luogu.org/problemnew/show/P2825
// [HEOI2016/TJOI2016]游戏

#include <bits/stdc++.h>
using namespace std;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
    static const int MAXN = 1000;
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
const int MAXN = 55;
int N, M;
int horzIdx[MAXN][MAXN], vertIdx[MAXN][MAXN];

int main() {
    memset(horzIdx, -1, sizeof(horzIdx));
    memset(vertIdx, -1, sizeof(vertIdx));
    scanf("%d%d", &N, &M);
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    int currHorzIdx = -1;
    for (int i = 0; i < N; i++) {
        int j = 0;
        while (j < M) {
            while (j < M && grid[i][j] == '#') j++;
            if (j == M) continue;
            currHorzIdx++;
            while (j < M && grid[i][j] != '#') {
                if (grid[i][j] == '*') {
                    horzIdx[i][j] = currHorzIdx;
                }
                j++;
            }
        }
    }

    int currVertIdx = -1;
    for (int j = 0; j < M; j++) {
        int i = 0;
        while (i < N) {
            while (i < N && grid[i][j] == '#') i++;
            if (i == N) continue;
            currVertIdx++;
            while (i < N && grid[i][j] != '#') {
                if (grid[i][j] == '*') {
                    vertIdx[i][j] = currVertIdx;
                }
                i++;
            }
        }
    }

    Hungarian hungarian;
    hungarian.reset(currHorzIdx+1, currVertIdx+1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int h = horzIdx[i][j];
            int v = vertIdx[i][j];
            if (h >= 0 && v >= 0) {
                hungarian.addEdge(h, v);
            }
        }
    }

    printf("%d\n", hungarian.maxMatch());

    return 0;
}
