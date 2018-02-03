// https://www.luogu.org/problemnew/show/P2944
// [USACO09MAR]地震损失2Earthquake Damage 2

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 6010;
    static const int MAXM = 94000;
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
    int q[MAXN];

    bool bfs(int s, int t) {
        memset(d, -1, sizeof(d));
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

const int MAXN = 3010;
bool conn[MAXN][MAXN];
bool report[MAXN];
int P, C, N;

int outId(int i) {
    return 2*i - 1;
}

int inId(int i) {
    return 2*i;
}

int main() {
    scanf("%d%d%d", &P, &C, &N);
    const int S = 0, T = 2*P + 1;
    Dinic dinic;
    for (int i = 0; i < C; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a == b) continue;
        if (a > b) swap(a, b);
        if (!conn[a][b]) {
            dinic.addEdge(outId(a), inId(b), Dinic::inf);
            dinic.addEdge(outId(b), inId(a), Dinic::inf);
            conn[a][b] = true;
        }
    }
    for (int i = 0; i < N; i++) {
        int r;
        scanf("%d", &r);
        report[r] = true;
    }
    for (int i = 1; i <= P; i++) {
        if (report[i]) {
            dinic.addEdge(inId(i), outId(i), Dinic::inf);
            dinic.addEdge(outId(i), T, Dinic::inf);
        } else {
            dinic.addEdge(inId(i), outId(i), 1);
        }
    }

    dinic.addEdge(inId(1), outId(1), Dinic::inf);
    dinic.addEdge(S, inId(1), Dinic::inf);

    printf("%d\n", dinic.dinic(S, T));
    return 0;
}
