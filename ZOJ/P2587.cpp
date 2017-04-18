// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2587
// Unique Attack

#include <bits/stdc++.h>
using namespace std;

class Dinic {
private:
    static const int inf = 0x3f3f3f3f;
    static const int MAXN = 810;
    static const int MAXM = 20010;
    int head[MAXN], q[MAXN];
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

    int fwd_bfs(int s) {
        int ret = 0;
        memset(vis, 0, sizeof(vis));
        int fron = 0, rear = 0;
        q[rear++] = s;
        vis[s] = true;
        while (fron < rear) {
            int u = q[fron];
            fron++;
            ret++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (!vis[v] && E[i].cap) {
                    q[rear++] = v;
                    vis[v] = true;
                }
            }
        }
        return ret;
    }

    int bwd_bfs(int t) {
        int ret = 0;
        memset(vis, 0, sizeof(vis));
        int fron = 0, rear = 0 ;
        q[rear++] = t;
        vis[t] = true;
        while (fron < rear) {
            int u = q[fron];
            fron++;
            ret++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (!vis[v] && E[i^1].cap) {
                    q[rear++] = v;
                    vis[v] = true;
                }
            }
        }
        return ret;
    }

private:
    int d[MAXN];
    bool vis[MAXN];


    bool bfs(int s, int t) {
        memset(d, -1, sizeof(d));
        int fron = 0, rear = 0;
        q[rear++] = t;
        d[t] = 0;
        while (fron < rear) {
            int u = q[fron];
            fron++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q[rear] = v;
                    rear++;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int i = head[x]; i != -1; i = E[i].next) {
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
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }
};

int main() {
    int N, M, A, B;
    Dinic dinic;
    while (scanf("%d%d%d%d", &N, &M, &A, &B) && (N + M + A + B)) {
        dinic.reset();
        for (int i = 0; i < M; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            dinic.addEdge(u, v, w, w);
        }
        dinic.dinic(A, B);
        int x = dinic.fwd_bfs(A);
        int y = dinic.bwd_bfs(B);
        if (x + y == N) {
            printf("UNIQUE\n");
        } else {
            printf("AMBIGUOUS\n");
        }
    }
    return 0;
}
