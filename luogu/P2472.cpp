// https://www.luogu.org/problemnew/show/P2472
// [SCOI2007]蜥蜴

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

int R, C, D;
int A[22][22];
bool B[22][22];

int node(int i, int j, int k) {
    return k*R*C + 1 + i*C + j;
}

bool escapable(int i, int j) {
    return i < D || j < D || i > R - 1 - D || j > C - 1 - D;
}

int dist(int x1, int y1, int x2, int y2) {
    return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
}

int main() {
    scanf("%d%d%d", &R, &C, &D);
    char line[40];
    for (int i = 0; i < R; i++) {
        scanf("%s", line);
        for (int j = 0; j < C; j++) {
            A[i][j] = line[j] - '0';
        }
    }
    int tot = 0;
    for (int i = 0; i < R; i++) {
        scanf("%s", line);
        for (int j = 0; j < C; j++) {
            B[i][j] = (line[j] == 'L');
            tot += B[i][j];
        }
    }

    const int sz = R*C*2 + 2;
    const int S = 0, T = sz-1;
    Dinic dinic(sz, R*C*85);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (B[i][j]) dinic.addEdge(S, node(i, j, 0), 1);
            if (A[i][j]) dinic.addEdge(node(i, j, 0), node(i, j, 1), A[i][j]);
            if (escapable(i, j)) {
                dinic.addEdge(node(i, j, 1), T, Dinic::inf);
            }
            for (int x = 0; x < R; x++) {
                for (int y = 0; y < C; y++) {
                    if (x == i && y == j) continue;
                    if (dist(i, j, x, y) <= D*D) {
                        dinic.addEdge(node(i, j, 1),
                                      node(x, y, 0),
                                      Dinic::inf);
                    }
                }
            }
        }
    }
    int ans = dinic.dinic(S, T);
    printf("%d\n", tot - ans);
    return 0;
}
