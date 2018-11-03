// https://www.luogu.org/problemnew/show/P2765
// 魔术球问题

#include <bits/stdc++.h>
using namespace std;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
    int nx_, ny_;
    bool** g_;

public:
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
bool isSquare(int x) {
    int root = sqrt(x) + 0.1;
    return root * root == x;
}

void traverse(const Hungarian &hungarian, int n, vector<bool> &vis) {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int u = i;
            while (u != -1) {
                vis[u] = true;
                printf("%d ", u);
                u = hungarian.cx_[u];
            }
            printf("\n");
        }
    }
}

int N;

int solve(int n, bool print=false) {
    Hungarian hungarian(n+1, n+1);
    for (int i = 1; i < n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (isSquare(i+j)) {
                //printf("%d %d\n", i, j);
                hungarian.addEdge(i, j);
            }
        }
    }

    int ans = n - hungarian.maxMatch();
    if (print) {
        printf("%d\n", n);
        vector<bool> vis(n+1, false);
        traverse(hungarian, n, vis);
    }

    return ans;
}

int main() {
    cin >> N;
    int lo = 1, hi = 1600;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (solve(mid) > N) hi = mid;
        else lo = mid;
    }
    solve(lo, true);
    return 0;
}
