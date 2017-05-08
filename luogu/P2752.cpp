// https://www.luogu.org/problem/show?pid=2752
// [USACO4.3]街道赛跑Street Race

#include <bits/stdc++.h>
using namespace std;

bool iscut[100];

class Graph {
    static const int MAXM = 400;
public:
    struct Edge {
        int next, to;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }

    bool bfs(int x) {
        queue<int> q;
        q.push(0);
        vector<bool> vis(N);
        vis[0] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == N-1) return true;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (!vis[v] && v != x) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        return false;
    }
};

class DFS {
public:
    static const int MAXN = 100;
    static const int MAXM = 400;

    struct Edge {
        int next, to;
    } E[MAXM];

    int head[MAXN], dfn[MAXN], low[MAXN];
    bool vis[MAXN], instack[MAXN];
    int eidx;
    int tmpdfn;
    int N;

    DFS(int N_):N(N_) {
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        memset(vis, 0, sizeof(vis));
        memset(instack, 0, sizeof(instack));
        tmpdfn = 0;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }

    void dfs(int u, int father) {
        vis[u] = true;
        dfn[u] = low[u] = tmpdfn++;
        for (int i = head[u]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (v != father && vis[v]) {
                low[u] = min(low[u], dfn[v]);
            }
            if (!vis[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                // if low[v] > dfn[u], (u, v) is a bridge
                // if low[v] >= dfn[u], u is a cut vertex
                if (low[v] >= dfn[u]) iscut[u] = true;
            }
        }
    }
};

int main() {
    vector<vector<int>> adj;
    while (true) {
        int x;
        scanf("%d", &x);
        if (x == -1) break;
        adj.push_back(vector<int>());
        while (x != -2) {
            adj.back().push_back(x);
            scanf("%d", &x);
        }
    }

    int N = adj.size();
    Graph graph(N);
    for (int i = 0; i < (int)adj.size(); i++) {
        for (int v: adj[i]) {
            graph.addEdge(i, v);
        }
    }

    vector<int> inevitable;
    for (int x = 1; x < N-1; x++) {
        if (!graph.bfs(x)) {
            inevitable.push_back(x);
        }
    }

    printf("%d ", inevitable.size());
    for (int x: inevitable) {
        printf("%d ", x);
    }
    printf("\n");

    DFS dfs(N);
    for (int i = 0; i < (int)adj.size(); i++) {
        for (int v: adj[i]) {
            dfs.addEdge(i, v);
            dfs.addEdge(v, i);
        }
    }
    dfs.dfs(0, -1);
    vector<int> middle;
    for (int x: inevitable) {
        if (iscut[x]) {
            middle.push_back(x);
        }
    }
    printf("%d ", middle.size());
    for (int x: middle) {
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}
