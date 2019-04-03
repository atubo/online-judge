// https://www.luogu.org/problemnew/show/P4294
// [WC2008]游览计划

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};
const int MAXN = 12;
int N, M;
int A[MAXN][MAXN];
int tid[MAXN][MAXN];
bool vis[MAXN][MAXN];
char sol[MAXN][MAXN];

struct Node {
    int j, s;
} nodes[1<<10][100];

int encode(int i, int j) {
    return i*M + j;
}

void decode(int x, int &i, int &j) {
    j = x % M;
    i = x / M;
}

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}


class SteinerTreeFloyd {
public:
    SteinerTreeFloyd(int n, const vector<int> &t):
        n_(n), r_(t.size()), ALL((1<<r_)-1), t_(t) {
        alloc();
    }

    ~SteinerTreeFloyd() {
        dealloc();
    }

    void addEdge(int u, int v, int w) {
        g_[u][v] = min(g_[u][v], w);
    }

    void solve() {
        for (int k = 0; k < n_; k++) {
            for (int i = 0; i < n_; i++) {
                for (int j = 0; j < n_; j++) {
                    g_[i][j] = min(g_[i][j], g_[i][k] + g_[k][j]);
                }
            }
        }
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < n_; j++) {
                int x, y;
                decode(j, x, y);
                g_[i][j] += A[x][y];
            }
        }

        for (int i = 0; i < r_; i++) {
            for (int j = 0; j < n_; j++) {
                dp[1<<i][j] = g_[t_[i]][j];
            }
        }

        for (int i = 1; i <= ALL; i++) {
            if (!(i&(i-1))) continue;
            for (int j = 0; j < n_; j++) dp[i][j] = INF;
            for (int j = 0; j < n_; j++) {
                int x, y;
                decode(j, x, y);
                int tmp = INF;
                int mins = -1;
                for (int s = i&(i-1); s; s=i&(s-1)) {
                    int v = dp[s][j] + dp[i^s][j];
                    if (v < tmp) {
                        tmp = v;
                        mins = s;
                    }
                }
                for (int k = 0; k < n_; k++) {
                    int v = g_[j][k]-2*A[x][y]+tmp;
                    if (v < dp[i][k]) {
                        dp[i][k] = v;
                        nodes[i][k] = {j, mins};
                    }
                }
            }
        }
    }

    void search(int s, int u, vector<int> &path) {
        assert(s != 0);
        auto node = nodes[s][u];
        int j = node.j;
        int t = node.s;
        memset(vis, 0, sizeof(vis));
        if (t != 0) {
            addPath(u, j, path);
            search(t, j, path);
            search(s^t, j, path);
        } else {
            assert(__builtin_popcount(s) == 1);
            int v = t_[__builtin_ctz(s)];
            addPath(u, v, path);
        }

    }

    bool addPath(int p, int q, vector<int> &path) {
        if (p == q) {
            path.push_back(p);
            return true;
        }
        int x, y;
        decode(p, x, y);
        vis[x][y] = true;
        for (int d = 0; d < 4; d++) {
            int x1 = x + DX[d];
            int y1 = y + DY[d];
            int r = encode(x1, y1);
            if (inRange(x1, y1) && !vis[x1][y1] &&
                A[x][y] + g_[r][q] == g_[p][q]) {
                if (addPath(r, q, path)) {
                    path.push_back(p);
                    return true;
                }
            }
        }
        return false;
    }


    int **dp;

private:
    int n_;
    int r_;
    const int ALL;
    const vector<int> &t_;
    int **g_;

    const int INF = 0x3F3F3F3F;

    void alloc() {
        dp = new int*[1<<r_]{};
        for (int i = 0; i <= ALL; i++) {
            dp[i] = new int[n_]{};
        }

        g_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            g_[i] = new int[n_]{};
            for (int j = 0; j < n_; j++) g_[i][j] = INF;
            g_[i][i] = 0;
        }
    }

    void dealloc() {
        for (int i = 0; i <= ALL; i++) {
            delete dp[i];
        }
        delete[] dp;

        for (int i = 0; i < n_; i++) {
            delete g_[i];
        }
        delete g_;
    }
};

int main() {
    memset(tid, -1, sizeof(tid));
    scanf("%d%d", &N, &M);
    vector<int> terminals;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
            if (A[i][j] == 0) {
                tid[i][j] = terminals.size();
                terminals.push_back(encode(i, j));
            }
        }
    }
    SteinerTreeFloyd st(N*M, terminals);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int d = 0; d < 4; d++) {
                int x = i + DX[d];
                int y = j + DY[d];
                if (inRange(x, y)) {
                    st.addEdge(encode(i, j), encode(x, y), A[i][j]);
                }
            }
        }
    }
    st.solve();

    const int ALL = (1<<terminals.size()) - 1;
    int ans = st.dp[ALL][terminals[0]];
    printf("%d\n", ans);

    vector<int> path;
    st.search(ALL, terminals[0], path);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tid[i][j] >= 0) sol[i][j] = 'x';
            else sol[i][j] = '_';
        }
    }
    for (int u: path) {
        int x, y;
        decode(u, x, y);
        if (tid[x][y] < 0) sol[x][y] = 'o';
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", sol[i][j]);
        }
        printf("\n");
    }

    return 0;
}
