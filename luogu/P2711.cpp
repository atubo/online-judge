// https://www.luogu.org/problem/show?pid=2711
// 小行星

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 2500;
    static const int MAXM = 250000;
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

using TI = tuple<int, int, int>;

int main() {
    unordered_map<int, int> xmap, ymap, zmap;
    int N;
    scanf("%d", &N);
    vector<TI> stars(N);
    int nx = 0, ny = 0, nz = 0;
    for (int i = 0; i < N; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (xmap.count(x) == 0) xmap[x] = ++nx;
        if (ymap.count(y) == 0) ymap[y] = ++ny;
        if (zmap.count(z) == 0) zmap[z] = ++nz;
        stars[i] = make_tuple(xmap[x], ymap[y], zmap[z]);
    }

    Dinic dinic;
    const int S = 0, T = nx + 2*ny + nz + 1;
    for (int i = 1; i <= nx; i++) {
        dinic.addEdge(S, i, 1);
    }
    for (int i = 1; i <= ny; i++) {
        dinic.addEdge(nx+i, nx+ny+i, 1);
    }
    for (int i = 1; i <= nz; i++) {
        dinic.addEdge(nx+2*ny+i, T, 1);
    }

    for (const TI& s: stars) {
        int x, y, z;
        tie(x, y, z) = s;
        dinic.addEdge(x, nx+y, Dinic::inf);
        dinic.addEdge(nx+ny+y, nx+2*ny+z, Dinic::inf);
    }

    printf("%d\n", dinic.dinic(S, T));
    return 0;
}
