// https://www.luogu.org/problemnew/show/P4311
// 士兵占领

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
    struct Edge {
        int to, next, cap;
    };

    const int N, MAXM;
    int *head;
    Edge *E;
    int e;
private:
    int *curr;

public:
    Dinic(int N_, int M_): N(N_), MAXM(2*M_) {
        alloc();
        reset();
    }

    ~Dinic() {
        dealloc();
    }

    void reset() {
        e = 0;
        memset(head, -1, N * sizeof(int));
    }

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

    int dinic(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }

private:
    void alloc() {
        head = new int[N]{};
        curr = new int[N]{};
        E    = new Edge[MAXM]{};
        d    = new int[N]{};
        q    = new int[N]{};
    }

    void dealloc() {
        delete[] head;
        delete[] curr;
        delete[] E;
        delete[] d;
        delete[] q;
    }

    int *d;
    int *q;

    bool bfs(int s, int t) {
        memset(d, -1, N * sizeof(int));
        int front = 0, back = 0;
        q[back++] = t;

        d[t] = 0;
        while (front != back) {
            int u = q[front];
            front++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
        }
        return ret;
    }
};

const int MAXN = 110;
int M, N, K;
int L[MAXN], C[MAXN];
int row_block[MAXN], col_block[MAXN];
bool blocked[MAXN][MAXN];

int solve() {
    Dinic dinic(M+N+2, M+N+M*N);
    const int src = 0, snk = M+N+1;
    for (int i = 0; i < M; i++) {
        int cap = N - L[i] - row_block[i];
        if (cap < 0) return -1;
        dinic.addEdge(src, i+1, cap);
    }
    for (int i = 0; i < N; i++) {
        int cap = M - C[i] - col_block[i];
        if (cap < 0) return -1;
        dinic.addEdge(M+1+i, snk, cap);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!blocked[i][j]) {
                dinic.addEdge(i+1, M+1+j, 1);
            }
        }
    }
    return M*N - K - dinic.dinic(src, snk);
}

int main() {
    scanf("%d%d%d", &M, &N, &K);
    for (int i = 0; i < M; i++) {
        scanf("%d", &L[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        row_block[x]++;
        col_block[y]++;
        blocked[x][y] = true;
    }

    int ans = solve();
    if (ans != -1) {
        printf("%d\n", ans);
    } else {
        printf("JIONG!\n");
    }

    return 0;
}
