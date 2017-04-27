// https://www.luogu.org/problem/show?pid=2417
// 课程

#include <bits/stdc++.h>
using namespace std;

class Hungarian {
private:
    static const int MAXN = 500;
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
    int nt;
    scanf("%d", &nt);
    Hungarian hungarian;
    while (nt--) {
        int p, n;
        scanf("%d%d", &p, &n);
        hungarian.reset(p, n);
        for (int i = 0; i < p; i++) {
            int m;
            scanf("%d", &m);
            for (int j = 0; j < m; j++) {
                int u;
                scanf("%d", &u);
                hungarian.addEdge(i, u-1);
            }
        }
        int maxmatch = hungarian.maxMatch();
        printf(p == maxmatch ? "YES\n" : "NO\n");
    }
    return 0;
}
