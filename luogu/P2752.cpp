// https://www.luogu.org/problem/show?pid=2752
// [USACO4.3]街道赛跑Street Race

#include <bits/stdc++.h>
using namespace std;

class Graph {
    static const int MAXM = 400;
public:
    struct Edge {
        int next, to;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;
    vector<int> dist;

    Graph(int N_):N(N_) {
        head.resize(N);
        dist.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
            dist[i] = -1;
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

    bool bfs2(int x) {
        vector<bool> vis(N);
        queue<int> q;
        q.push(x);
        vis[x] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (dist[v] < dist[x]) return false;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        return true;
    }

    void bfs3() {
        queue<int> q;
        q.push(0);
        dist[0] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (dist[v] == -1) {
                    q.push(v);
                    dist[v] = dist[u] + 1;
                }
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

    graph.bfs3();

    vector<int> middle;
    for (int x: inevitable) {
        if (graph.bfs2(x)) {
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
