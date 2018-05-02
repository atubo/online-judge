// https://www.luogu.org/problemnew/show/P1935
// [国家集训队]圈地计划

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
int N, M;
int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];
const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

int id(int i, int j) {
    return 1 + i*M + j;
}

bool inRange(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &C[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i+j) & 1) swap(A[i][j], B[i][j]);
        }
    }

    int64_t tot = 0;
    const int S = 0, T = N*M+1;
    Dinic dinic(T+1, 6*N*M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dinic.addEdge(S, id(i, j), A[i][j]);
            tot += A[i][j];
            dinic.addEdge(id(i, j), T, B[i][j]);
            tot += B[i][j];
            for (int d = 0; d < 4; d++) {
                int p = i + DX[d];
                int q = j + DY[d];
                if (inRange(p, q)) {
                    dinic.addEdge(id(i, j), id(p, q), C[i][j]+C[p][q]);
                    tot += C[i][j];
                }
            }
        }
    }

    int64_t flow = dinic.dinic(S, T);
    printf("%lld\n", tot - flow);

    return 0;
}
