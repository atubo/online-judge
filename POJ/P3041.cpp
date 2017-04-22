// http://poj.org/problem?id=3041
// Asteroids

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 1010;
    static const int MAXM = 25000;
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
        E[e].to = y; E[e].next = head[x]; E[e].cap = w;
        head[x] = e++;
        E[e].to = x; E[e].next = head[y]; E[e].cap = rw;
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
    int N, K;
    scanf("%d%d", &N, &K);

    Dinic dinic;
    const int S = 0, T = 2*N + 1;
    for (int i = 1; i <= N; i++) {
        dinic.addEdge(S, i, 1);
    }
    for (int i = N+1; i <= 2*N; i++) {
        dinic.addEdge(i, T, 1);
    }

    for (int i = 0; i < K; i++) {
        int r, c;
        scanf("%d%d", &r, &c);
        dinic.addEdge(r, N+c, Dinic::inf);
    }
    printf("%d\n", dinic.dinic(S, T));
    return 0;
}
