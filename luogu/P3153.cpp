// https://www.luogu.org/problemnew/show/P3153
// [CQOI2009]DANCE跳舞

#include <bits/stdc++.h>
using namespace std;


class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 5400;
    static const int MAXM = 16000;
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

int N, K, Q;
bool like[52][52];
Dinic dinic;

int metanode(int i) {
    return i*Q + N + 1;
}

int likenode(int i) {
    return i*Q + N + 2;
}

int dislikenode(int i) {
    return i*Q + N + 3;
}

int pairnode(int i, int j) {
    return i*Q + j + 1;
}

bool solve(int cap) {
    dinic.reset();
    Q = N + 3;
    const int S = 0, T = 2 * N * Q + 1;
    // boys
    for (int i = 0; i < N; i++) {
        dinic.addEdge(S, metanode(i), cap);
        dinic.addEdge(metanode(i), likenode(i), N);
        dinic.addEdge(metanode(i), dislikenode(i), K);
    }
    // girls
    for (int i = N; i < 2*N; i++) {
        dinic.addEdge(metanode(i), T, cap);
        dinic.addEdge(likenode(i), metanode(i), N);
        dinic.addEdge(dislikenode(i), metanode(i), K);
    }

    for (int b = 0; b < N; b++) {
        for (int g = N; g < 2*N; g++) {
            if (like[b][g-N]) {
                dinic.addEdge(likenode(b), pairnode(b, g-N), 1);
                dinic.addEdge(pairnode(b, g-N), pairnode(g, b), 1);
                dinic.addEdge(pairnode(g, b), likenode(g), 1);
            } else {
                dinic.addEdge(dislikenode(b), pairnode(b, g-N), 1);
                dinic.addEdge(pairnode(b, g-N), pairnode(g, b), 1);
                dinic.addEdge(pairnode(g, b), dislikenode(g), 1);
            }
        }
    }

    int flow = dinic.dinic(S, T);
    return flow == N * cap;
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        char line[52];
        scanf("%s", line);
        for (int j = 0; j < N; j++) {
            like[i][j] = (line[j] == 'Y');
        }
    }

    int ret = 0;
    if (solve(1)) {
        int lo = 1, hi = N+1;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (solve(mid)) lo = mid;
            else            hi = mid;
        }
        ret = lo;
    }

    printf("%d\n", ret);

    return 0;
}
