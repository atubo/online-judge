// https://www.luogu.org/problem/show?pid=2055
// [ZJOI2009]假期的宿舍

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
int bed[MAXN];
int adj[MAXN][MAXN];
int isStudent[MAXN], leave[MAXN];
int N;

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

int main() {
    int tests;
    scanf("%d", &tests);
    Hungarian hungarian;
    while (tests--) {
        scanf("%d", &N);
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d", &isStudent[i]);
        }
        for (int i = 0; i < N; i++) {
            int x;
            scanf("%d", &x);
            if (isStudent[i]) {
                leave[i] = x;
                bed[i] = cnt++;
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &adj[i][j]);
            }
            adj[i][i] = 1;
        }

        hungarian.reset(N, cnt);
        int needed = 0;
        for (int i = 0; i < N; i++) {
            if (isStudent[i] && leave[i]) continue;
            needed++;
            for (int j = 0; j < N; j++) {
                if (adj[i][j] && isStudent[j]) {
                    hungarian.addEdge(i, bed[j]);
                }
            }
        }

        int match = hungarian.maxMatch();
        printf(match == needed ? "^_^\n" : "T_T\n");
    }
    return 0;
}
