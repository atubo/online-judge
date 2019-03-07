// https://www.luogu.org/problemnew/show/P2526
// [SHOI2001]小狗散步

#include <bits/stdc++.h>
using namespace std;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
    int nx_, ny_;
    bool** g_;

    int *cx_, *cy_;
    bool *mk_;

    void alloc() {
        g_ = new bool*[nx_];
        for (int i = 0; i < nx_; i++) {
            g_[i] = new bool[ny_];
        }
        cx_ = new int[nx_];
        cy_ = new int[ny_];
        mk_ = new bool[ny_];
    }

    void dealloc() {
        for (int i = 0; i < nx_; i++) {
            delete[] g_[i];
        }
        delete[] g_;

        delete[] cx_;
        delete[] cy_;
        delete[] mk_;
    }

    int path(int u) {
        for (int v = 0; v < ny_; v++) {
            if (g_[u][v] && !mk_[v]) {
                mk_[v] = true;
                if (cy_[v] == -1 || path(cy_[v])) {
                    cx_[u] = v;
                    cy_[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

public:
    Hungarian(int nx, int ny): nx_(nx), ny_(ny) {
        alloc();
        reset();
    }

    ~Hungarian() {
        dealloc();
    }

    void reset() {
        for (int i = 0; i < nx_; i++) {
            memset(g_[i], 0, ny_ * sizeof(bool));
        }
    }

    void addEdge(int x, int y) {
        g_[x][y] = true;
    }

    int maxMatch() {
        int res = 0;
        memset(cx_, -1, nx_ * sizeof(int));
        memset(cy_, -1, ny_ * sizeof(int));
        for (int i = 0; i < nx_; i++) {
            if (cx_[i] == -1) {
                memset(mk_, 0, ny_ * sizeof(bool));
                res += path(i);
            }
        }
        return res;
    }

    struct Match {
        int nx, ny;
        const int *cx, *cy;
        bool const * const *g;
    };

    Match getMatch() const {
        return {nx_, ny_, cx_, cy_, g_};
    }
};
const int MAXN = 110;
int N, M;

struct Point {
    int x, y;
};

Point P1[MAXN], P2[MAXN];

double dist(const Point &p1, const Point &p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}


bool check(int i, int j) {
    double d1 = dist(P1[j], P1[j+1]);
    double d2 = dist(P1[j], P2[i]) + dist(P2[i], P1[j+1]);
    return d2 <= d1*2;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        int x,  y;
        scanf("%d%d", &x, &y);
        P1[i] = {x, y};
    }
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        P2[i] = {x, y};
    }

    Hungarian hungarian(M, N-1);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N-1; j++) {
            if (check(i, j)) {
                hungarian.addEdge(i, j);
            }
        }
    }
    int ans = hungarian.maxMatch();
    printf("%d\n", ans + N);
    auto match = hungarian.getMatch();
    for (int i = 0; i < N-1; i++) {
        printf("%d %d ", P1[i].x, P1[i].y);
        int j = match.cy[i];
        if (j != -1) {
            printf("%d %d ", P2[j].x, P2[j].y);
        }
    }
    printf("%d %d", P1[N-1].x, P1[N-1].y);

    return 0;
}
