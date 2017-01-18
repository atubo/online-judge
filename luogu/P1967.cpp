// https://www.luogu.org/problem/show?pid=1967
// P1967 货车运输

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <functional>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};


typedef pair<int, int> PII;
typedef pair<int, PII> Edge;

class Solution {
public:
    int N, M;
    int MAXB;
    vector<vector<PII> > adj;   // (node, weight)
    vector<int> depth;
    vector<vector<int> > father;
    vector<vector<int> > minWgt;

    UnionFind* uf;

public:
    Solution() {
        scanf("%d %d", &N, &M);
        vector<Edge> edges(M);
        for (int i = 0; i < M; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            x--; y--;
            edges[i] = make_pair(z, make_pair(x, y));
        }

        adj.resize(N);
        uf = new UnionFind(N);
        sort(edges.begin(), edges.end(), greater<Edge>());
        for (int i = 0; i < (int)edges.size(); i++) {
            const Edge& e = edges[i];
            int w = e.first;
            int u = e.second.first;
            int v = e.second.second;
            if (uf->find(u) == uf->find(v)) continue;
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
            uf->join(u, v);
        }
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
           MAXB++;
           x = x * 2;
        }

        depth.resize(N);
        father.resize(N);
        minWgt.resize(N);
        for (int i = 0; i < N; i++) {
            father[i].resize(MAXB, -1);
            minWgt[i].resize(MAXB, INT_MAX);
        }

        vector<bool> visited(N, false);
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                dfs(i, -1, 0, visited, 0);
            }
        }

        binaryLift();
    }

    void solve() {
        int q;
        scanf("%d", &q);
        while (q--) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;
            printf("%d\n", findMinWeight(x, y));
        }
    }

    void dfs(int x, int f, int w, vector<bool>& visited, int d) {
        depth[x] = d;
        father[x][0] = f;
        minWgt[x][0] = w;
        visited[x] = true;
        for (int i = 0; i < (int)adj[x].size(); i++) {
            int u = adj[x][i].first;
            int wt = adj[x][i].second;
            if (!visited[u]) dfs(u, x, wt, visited, d+1);
        }
    }

    void binaryLift() {
        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i < N; i++) {
                if (father[i][j-1] != -1) {
                    minWgt[i][j] = min(minWgt[i][j-1], minWgt[father[i][j-1]][j-1]);
                    father[i][j] = father[father[i][j-1]][j-1];
                }
            }
        }
    }

    int findMinWeight(int u, int v) {
        if (uf->find(u) != uf->find(v)) return -1;
        int ans = INT_MAX;
        if (depth[u] < depth[v]) swap(u, v);
        for (int b = MAXB-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (depth[father[u][b]] >= depth[v]) {
                ans = min(ans, minWgt[u][b]);
                u = father[u][b];
            }
        }

        if (u == v) return ans;

        for (int b = MAXB-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (father[u][b] != father[v][b]) {
                ans = min(ans, minWgt[u][b]);
                ans = min(ans, minWgt[v][b]);
                u = father[u][b];
                v = father[v][b];
            }
        }
        return min(ans, minWgt[u][0]);
    }
};

int main() {
    Solution solution;
    solution.preCompute();
    solution.solve();
    return 0;
}
