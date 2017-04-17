// https://www.luogu.org/problem/show?pid=1231
// 教辅的组成

#include <bits/stdc++.h>
using namespace std;

namespace Dinic {
const int inf = 0x3f3f3f3f;
const int maxn = 1000000;
int e, be[maxn], ne[maxn], to[maxn], c[maxn];

void init() {
    memset(be, -1, sizeof(be));
}

void addEdge(int x, int y, int z) {
    to[e] = y, ne[e] = be[x], be[x] = e;
    c[e] = z, e++;
    to[e] = x, ne[e] = be[y], be[y] = e;
    c[e] = 0, e++;
}

int d[maxn], end;


bool bfs() {
    queue<int> q;
    memset(d, -1, sizeof(d));
    q.push(end);
    d[end] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = be[u]; i != -1; i = ne[i]) {
            int v = to[i];
            if (d[v] == -1 && c[i^1]) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[0] != -1;
}

int dfs(int x, int low) {
    if (x == end || !low) return low;
    int ret = 0;
    for (int i = be[x]; i != -1; i = ne[i]) {
        int v = to[i];
        if (d[v] == d[x] - 1) {
            int k = dfs(v, min(low-ret, c[i]));
            if (k > 0) {
                c[i] -= k;
                c[i^1] += k;
                ret += k;
            }
        }
    }
    return ret;
}

int dinic() {
    int ans = 0;
    while (bfs()) {
        int k = dfs(0, inf);
        if (k > 0) ans += k;
    }
    return ans;
}
}


int N1, N2, N3, M1, M2;

int main() {
    Dinic::init();
    scanf("%d%d%d", &N1, &N2, &N3);
    const int S = 0, T = 2*N1+N2+N3+1;
    Dinic::end = T;

    for (int i = 1; i <= N2; i++) {
        Dinic::addEdge(S, i, 1);
    }
    for (int i = 2*N1+N2+1; i <= 2*N1+N2+N3; i++) {
        Dinic::addEdge(i, T, 1);
    }
    for (int i = 1; i <= N1; i++) {
        Dinic::addEdge(N2+2*i-1, N2+2*i, 1);
    }

    scanf("%d", &M1);
    int x, y;
    for (int i = 0; i < M1; i++) {
        scanf("%d%d", &x, &y);
        Dinic::addEdge(y, N2+2*x-1, 1);
    }

    scanf("%d", &M2);
    for (int i = 0; i < M2; i++) {
        scanf("%d%d", &x, &y);
        Dinic::addEdge(N2+2*x, 2*N1+N2+y, 1);
    }

    printf("%d\n", Dinic::dinic());
    return 0;
}
