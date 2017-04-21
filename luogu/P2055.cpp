// https://www.luogu.org/problem/show?pid=2055
// [ZJOI2009]假期的宿舍

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
int bed[MAXN];
int adj[MAXN][MAXN];
int isStudent[MAXN], leave[MAXN];
int N;

class Dinic {
private:
    static const int inf = 0x3f3f3f3f;
    static const int MAXM = 5 * MAXN * MAXN;
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

int main() {
    int tests;
    scanf("%d", &tests);
    Dinic dinic;
    while (tests--) {
        scanf("%d", &N);
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d", &isStudent[i]);
        }
        for (int i = 0; i < N; i++) {
            int x;
            scanf("%d", &x);
            if (isStudent[i]) {
                leave[i] = x;
                bed[i] = cnt++;
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &adj[i][j]);
            }
            adj[i][i] = 1;
        }

        dinic.reset();
        const int S = 0, T = N + cnt + 1;
        int needed = 0;
        for (int i = 1; i <= N; i++) {
            if (!(isStudent[i-1] && leave[i-1])) {
                dinic.addEdge(S, i, 1);
                needed++;
            }
        }

        for (int i = 1; i <= cnt; i++) {
            dinic.addEdge(N+i, T, 1);
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (adj[i][j] && isStudent[j]) {
                    dinic.addEdge(i+1, N+bed[j]+1, 1);
                }
            }
        }

        int flow = dinic.dinic(S, T);
        printf(flow == needed ? "^_^\n" : "T_T\n");
    }
    return 0;
}
