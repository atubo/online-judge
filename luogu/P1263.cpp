// https://www.luogu.org/problemnew/show/P1263
// 宫廷守卫

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

const int MAXN = 210;
int M, N;
int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];
int X[MAXN*MAXN], Y[MAXN*MAXN];

void build() {
    int nx = 0;
    for (int i = 0; i < M; i++) {
        int p = 0;
        while (p < N) {
            while (p < N && A[i][p] != 0) p++;
            if (p == N) break;
            int q = p+1;
            while (q < N && A[i][q] != 2) q++;
            for (int j = p; j < q; j++) {
                B[i][j] = nx;
                X[nx] = i;
            }
            nx++;
            p = q;
        }
    }

    int ny = 0;
    for (int i = 0; i < N; i++) {
        int p = 0;
        while (p < M) {
            while (p < M && A[p][i] != 0) p++;
            if (p == M) break;
            int q = p+1;
            while (q < M && A[q][i] != 2) q++;
            for (int j = p; j < q; j++) {
                C[j][i] = ny;
                Y[ny] = i;
            }
            ny++;
            p = q;
        }
    }

    Hungarian hungarian(nx, ny);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] == 0) hungarian.addEdge(B[i][j], C[i][j]);
        }
    }

    int ans = hungarian.maxMatch();
    printf("%d\n", ans);
    auto match = hungarian.getMatch();
    for (int i = 0; i < nx; i++) {
        int cx = match.cx[i];
        if (cx != -1) {
            int x = X[i];
            int y = Y[cx];
            printf("%d %d\n", x+1, y+1);
        }
    }
}


void solve() {
    build();
}

int main() {
    memset(B, -1, sizeof(B));
    memset(C, -1, sizeof(C));
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    solve();

    return 0;
}
