// https://www.luogu.org/problemnew/show/P3227
// [HNOI2013]切糕

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

int P, Q, R;
int D;
int A[42][42][42];

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

int node(int i, int j, int k) {
    return 1 + k*P*Q + i*Q + j;
}

bool inRange(int x, int y, int z) {
    return 0 <= x && x < P && 0 <= y && y < Q
        && 0 <= z && z <= R;
}

int main() {
    scanf("%d%d%d", &P, &Q, &R);
    scanf("%d", &D);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < Q; k++) {
                scanf("%d", &A[j][k][i]);
            }
        }
    }

    const int sz = 2 + (R+1) * P * Q;
    const int S = 0, T = sz-1;
    Dinic dinic(sz, P*Q*(5*R+2));

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < Q; j++) {
            dinic.addEdge(S, node(i, j, 0), Dinic::inf);
            dinic.addEdge(node(i, j, R), T, Dinic::inf);
        }
    }

    for (int k = 0; k < R; k++) {
        for (int i = 0; i < P; i++) {
            for (int j = 0; j < Q; j++) {
                dinic.addEdge(node(i, j, k), node(i, j, k+1), A[i][j][k]);
                for (int d = 0; d < 4; d++) {
                    int x2 = i + DX[d];
                    int y2 = j + DY[d];
                    int z2 = k - D;
                    if (inRange(x2, y2, z2)) {
                        dinic.addEdge(node(i, j, k),
                                      node(x2, y2, z2),
                                      Dinic::inf);
                    }
                }
            }
        }
    }

    int ans = dinic.dinic(S, T);
    printf("%d\n", ans);

    return 0;
}
