// https://www.luogu.org/problemnew/show/P3231
// [HNOI2013]消毒

#include <bits/stdc++.h>
using namespace std;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
public:
    int nx_, ny_;
    bool** g_;

    int *cx_, *cy_;
    int *mk_;

    void alloc() {
        g_ = new bool*[nx_];
        for (int i = 0; i < nx_; i++) {
            g_[i] = new bool[ny_];
        }
        cx_ = new int[nx_];
        cy_ = new int[ny_];
        mk_ = new int[ny_];
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
                mk_[v] = 1;
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

    inline void addEdge(int x, int y) {
        g_[x][y] = true;
    }

    int maxMatch() {
        int res = 0;
        memset(cx_, -1, nx_ * sizeof(int));
        memset(cy_, -1, ny_ * sizeof(int));
        for (int i = 0; i < nx_; i++) {
            if (cx_[i] == -1) {
                memset(mk_, 0, ny_ * sizeof(int));
                res += path(i);
            }
        }
        return res;
    }
};

int T;
int A, B, C;
int dim[3];
bool ***space;
int **plane;

void alloc() {
    space = new bool**[dim[0]];
    for (int i = 0; i < dim[0]; i++) {
        space[i] = new bool*[dim[1]];
        for (int j = 0; j < dim[1]; j++) {
            space[i][j] = new bool[dim[2]]{};
        }
    }
    plane = new int*[dim[1]];
    for (int i = 0; i < dim[1]; i++) {
        plane[i] = new int[dim[2]]{};
    }
}

void dealloc() {
    for (int i = 0; i < dim[0]; i++) {
        for (int j = 0; j < dim[1]; j++) {
            delete[] space[i][j];
        }
        delete[] space[i];
    }
    delete[] space;

    for (int i = 0; i < dim[1]; i++) {
        delete[] plane[i];
    }
    delete[] plane;
}

int solve(Hungarian &hungarian, int x) {
    int ans = 0;

    hungarian.reset();
    for (int i = 0; i < dim[0]; i++) {
        if ((x >> i) & 1) {
            ans++;
        }
    }
    for (int i = 0; i < dim[1]; i++) {
        for (int j = 0; j < dim[2]; j++) {
            if (plane[i][j] & (~x)) {
                hungarian.g_[i][j] = true;
            }
        }
    }
    ans += hungarian.maxMatch();
    return ans;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &A, &B, &C);
        dim[0] = A;
        dim[1] = B;
        dim[2] = C;
        int min_idx = 0, min_v = A;
        for (int i = 1; i < 3; i++) {
            if (dim[i] < min_v) {
                min_v = dim[i];
                min_idx = i;
            }
        }
        rotate(dim, dim+min_idx, dim+3);

        alloc();

        for (int i = 0; i < A; i++) {
            for (int j = 0; j < B; j++) {
                for (int k = 0; k < C; k++) {
                    int x;
                    scanf("%d", &x);
                    if (min_idx == 0) {
                        space[i][j][k] = x;
                    } else if (min_idx == 1) {
                        space[j][k][i] = x;
                    } else {
                        space[k][i][j] = x;
                    }
                }
            }
        }
        for (int i = 0; i < dim[0]; i++) {
            for (int j = 0; j < dim[1]; j++) {
                for (int k = 0; k < dim[2]; k++) {
                    if (space[i][j][k]) {
                        plane[j][k] |= (1 << i);
                    }
                }
            }
        }
        int ans = INT_MAX;
        Hungarian hungarian(dim[1], dim[2]);
        for (int i = 0; i < (1<<dim[0]); i++) {
            ans = min(ans, solve(hungarian, i));
        }
        printf("%d\n", ans);

        dealloc();
    }

    return 0;
}
