// https://www.luogu.org/problemnew/show/P1263
// 宫廷守卫

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
    int nx_, ny_;
    Graph g_;
    int len_;

    int *cx_, *cy_;
    bool *mk_;
    int *restore_;

    void alloc() {
        cx_ = new int[nx_];
        cy_ = new int[ny_];
        mk_ = new bool[ny_]{};
        restore_ = new int[ny_];
    }

    void dealloc() {
        delete[] cx_;
        delete[] cy_;
        delete[] mk_;
        delete[] restore_;
    }

    int path(int u) {
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to - nx_;
            if (!mk_[v]) {
                mk_[v] = true;
                restore_[len_++] = v;
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
    Hungarian(int nx, int ny): nx_(nx), ny_(ny), g_(nx+ny, 200*200) {
        alloc();
    }

    ~Hungarian() {
        dealloc();
    }

    void addEdge(int x, int y) {
        g_.addEdge(x, nx_+y);
    }

    int maxMatch() {
        int res = 0;
        memset(cx_, -1, nx_ * sizeof(int));
        memset(cy_, -1, ny_ * sizeof(int));
        for (int i = 0; i < nx_; i++) {
            if (cx_[i] == -1) {
                len_ = 0;
                res += path(i);
                for (int j = 0; j < len_; j++) {
                    mk_[restore_[j]] = 0;
                }
            }
        }
        return res;
    }

    struct Match {
        int nx, ny;
        const int *cx, *cy;
    };

    Match getMatch() const {
        return {nx_, ny_, cx_, cy_};
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
