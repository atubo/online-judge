// https://www.luogu.org/problemnew/show/P2598
// [ZJOI2009]狼和羊的故事

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 10010;
    static const int MAXM = 80100;
    int head[MAXN], curr[MAXN];
    struct Edge {
        int to, next, cap;
    } E[MAXM];
    int e;

public:
    Dinic() {
        reset();
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

    bool bfs(int s, int t) {
        memset(d, -1, sizeof(d));
        queue<int> q;
        q.push(t);
        d[t] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q.push(v);
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

int N, M;
int F[110][110];

int encode(int i, int j) {
    return i * M + j;
}

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}

bool connect(int i, int j, int in, int jn) {
    int a = F[i][j];
    int b = F[in][jn];
    return (a == 1 && b == 0) ||
        (a == 0 && b == 0) ||
        (a == 1 && b == 2) ||
        (a == 0 && b == 2);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &F[i][j]);
        }
    }
    Dinic dinic;
    const int S = N*M, T = S + 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int node = encode(i, j);
            if (F[i][j] == 1) dinic.addEdge(S, node, Dinic::inf);
            if (F[i][j] == 2) dinic.addEdge(node, T, Dinic::inf);
            for (int d = 0; d < 4; d++) {
                int in = i + DX[d];
                int jn = j + DY[d];
                if (inRange(in, jn) && connect(i, j, in, jn)) {
                    int noden = encode(in, jn);
                    dinic.addEdge(node, noden, 1);
                }
            }
        }
    }

    printf("%d\n", dinic.dinic(S, T));
    return 0;
}
