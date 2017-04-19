// https://www.luogu.org/problem/show?pid=1656
// 炸铁路

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
vector<PII> keyroads;
void addKeyRoad(int u, int v) {
    if (u > v) swap(u, v);
    keyroads.push_back(make_pair(u, v));
}

// Note graph node is 0-indexed
class DFS {
public:
    static const int MAXN = 200;
    static const int MAXM = 10010;

    struct Edge {
        int next, to;
    } E[MAXM];

    int head[MAXN], dfn[MAXN], low[MAXN];
    bool vis[MAXN];
    int eidx;
    int N;

    DFS(int N_):N(N_) {
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        memset(vis, 0, sizeof(vis));
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }

    void dfs(int u, int father, int dth) {
        vis[u] = true;
        dfn[u] = low[u] = dth;
        for (int i = head[u]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (v != father && vis[v]) {
                low[u] = min(low[u], dfn[v]);
            }
            if (!vis[v]) {
                dfs(v, u, dth+1);
                low[u] = min(low[u], low[v]);
                // if low[v] > dfn[u], (u, v) is a bridge
                // if low[v] >= dfn[u], u is a cut vertex
                if (low[v] > dfn[u]) addKeyRoad(u, v);
            }
        }
    }
};

int N, M;
int main() {
    scanf("%d%d", &N, &M);
    DFS dfs(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        dfs.addEdge(u, v);
        dfs.addEdge(v, u);
    }
    dfs.dfs(0, -1, 0);
    sort(keyroads.begin(), keyroads.end());
    for (const PII& kr: keyroads) {
        printf("%d %d\n", kr.first+1, kr.second+1);
    }
    return 0;
}
