// https://www.luogu.org/problemnew/show/P2046
// [NOI2010]海拔

#include <bits/stdc++.h>
using namespace std;


class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 251100;
    static const int MAXM = 1003000;
    int head[MAXN], curr[MAXN];
    struct Edge {
        int to, next, cap;
    } ;
    int e;
    Edge *E;

public:
    Dinic() {
        E = new Edge[MAXM];
        reset();
    }

    ~Dinic() {
        delete[] E;
    }

    void reset() {
        e = 0;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

private:
    int d[MAXN];
    int q[MAXN];

    bool bfs(int s, int t) {
        memset(d, -1, sizeof(d));
        int front = 0, back = 0;
        q[back++] = t;
        d[t] = 0;
        while (back > front) {
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

public:
    int dinic(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < MAXN; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }
};

const int MAXN = 510;
int N;
int west[MAXN][MAXN], east[MAXN][MAXN];
int south[MAXN][MAXN], north[MAXN][MAXN];

int id(int i, int j) {
    return i * (N+1) + j;
}

int main() {
    scanf("%d", &N);
    Dinic dinic;
    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &east[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N+1; j++) {
            scanf("%d", &south[i][j]);
        }
    }
    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &west[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N+1; j++) {
            scanf("%d", &north[i][j]);
        }
    }

    const int S = (N+1) * (N+1), T = S + 1;
    dinic.addEdge(S, id(0, 0), Dinic::inf);
    dinic.addEdge(id(N, N), T, Dinic::inf);

    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N; j++) {
            dinic.addEdge(id(i, j), id(i, j+1), east[i][j], west[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N+1; j++) {
            dinic.addEdge(id(i, j), id(i+1, j), south[i][j], north[i][j]);
        }
    }

    printf("%d", dinic.dinic(S, T));
    return 0;
}
