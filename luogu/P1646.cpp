// https://www.luogu.org/problemnew/show/P1646
// [国家集训队]happiness

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 1.1e4;
    static const int MAXM = 8.1e4;
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

const int MAXN = 110;
int N, M;
int white[MAXN][MAXN], black[MAXN][MAXN];
int wwEast[MAXN][MAXN], bbEast[MAXN][MAXN];
int wwSouth[MAXN][MAXN], bbSouth[MAXN][MAXN];

int id(int i, int j) {
    return i * M + j;
}

int main() {
    scanf("%d%d", &N, &M);
    int tot = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &white[i][j]);
            tot += white[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &black[i][j]);
            tot += black[i][j];
        }
    }
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &wwSouth[i][j]);
            tot += wwSouth[i][j];
        }
    }
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &bbSouth[i][j]);
            tot += bbSouth[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M-1; j++) {
            scanf("%d", &wwEast[i][j]);
            tot += wwEast[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M-1; j++) {
            scanf("%d", &bbEast[i][j]);
            tot += bbEast[i][j];
        }
    }

    Dinic dinic;
    const int S = N*M, T = S+1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int src = 2 * white[i][j] + wwEast[i][j] + wwSouth[i][j];
            int sink = 2 * black[i][j] + bbEast[i][j] + bbSouth[i][j];
            if (i > 0) {
                src += wwSouth[i-1][j];
                sink += bbSouth[i-1][j];
            }
            if (j > 0) {
                src += wwEast[i][j-1];
                sink += bbEast[i][j-1];
            }
            dinic.addEdge(S, id(i, j), src);
            dinic.addEdge(id(i, j), T, sink);
            if (i < N-1) {
                int flow = wwSouth[i][j] + bbSouth[i][j];
                dinic.addEdge(id(i, j), id(i+1, j), flow, flow);
            }
            if (j < M-1) {
                int flow = wwEast[i][j] + bbEast[i][j];
                dinic.addEdge(id(i, j), id(i, j+1), flow, flow);
            }
        }
    }
    printf("%d\n", (2 * tot - dinic.dinic(S, T)) >> 1);

    return 0;
}
