// https://www.luogu.org/problemnew/show/P4589
// [TJOI2018]智力竞赛

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510;
bool mark[MAXN];

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
            if (g_[u][v] && !mk_[v] && !mark[v]) {
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
            if (!mark[i] && cx_[i] == -1) {
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

int N, M;
int V[MAXN];
int maxv, minv;
bool adj[MAXN][MAXN];

int pathCover(Hungarian &h, int th) {
    int above = 0;
    memset(mark, 0, sizeof(mark));
    for (int i = 0; i < M; i++) {
        if (V[i] >= th) {
            above++;
            mark[i] = true;
        }
    }
    return M - above - h.maxMatch();
}

int searchScore(Hungarian &h) {
    int lo = minv, hi = maxv+1;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (pathCover(h, mid) <= N) lo = mid;
        else hi = mid;
    }
    return lo;
}

void solve(Hungarian &h) {
    if (pathCover(h, maxv+1) <= N) {
        printf("AK\n");
    } else {
        int ans = searchScore(h);
        printf("%d\n", ans);
    }
}

void buildClosure() {
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                adj[i][j] |= (adj[i][k] && adj[k][j]);
            }
        }
    }
}

int main() {
    maxv = INT_MIN, minv = INT_MAX;
    scanf("%d%d", &N, &M);
    N++;
    for (int i = 0; i < M; i++) {
        scanf("%d", &V[i]);
        maxv = max(maxv, V[i]);
        minv = min(minv, V[i]);
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int a;
            scanf("%d", &a);
            a--;
            adj[i][a] = true;
        }
    }

    Hungarian hungarian(M, M);

    buildClosure();
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (adj[i][j]) hungarian.addEdge(i, j);
        }
    }
    solve(hungarian);

    return 0;
}
