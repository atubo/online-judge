// http://codeforces.com/problemset/problem/455/C
#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] != k) {
            parent[k] = find(parent[k]);
        }
        return parent[k];
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }
};
class Solution {
    using Adj = vector<vector<int>>;
private:
    int N, M, Q;
    Adj adj;
    UnionFind* uf;
    vector<int> D;
public:
    Solution() {
        cin >> N >> M >> Q;
        uf = new UnionFind(N);
        adj.resize(N);
        D.resize(N, 0);
        for (int i = 0; i < M; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
            uf->join(a, b);
        }
    }

    int dfs(int u, vector<bool>& visited) {
        visited[u] = true;
        int t, mx = 0;
        for (int v: adj[u]) {
            if (!visited[v]) {
                D[uf->find(u)] = max(D[uf->find(u)], mx + (t = 1 + dfs(v, visited)));
                mx = max(mx, t);
            }
        }
        return mx;
    }

    void solve() {
        vector<bool> visited(N, false);
        for (int i = 0; i < N; i++) {
            if (!visited[i]) dfs(i, visited);
           
        }

        for (int q = 0; q < Q; q++) {
            int t, x, y;
            scanf("%d", &t);
            if (t == 1) {
                scanf("%d", &x);
                x--;
                cout << D[uf->find(x)] << endl;
            } else {
                scanf("%d %d", &x, &y);
                x--;
                y--;
                int root_x = uf->find(x);
                int root_y = uf->find(y);
                if (root_x != root_y) {
                    int d1 = D[root_x];
                    int d2 = D[root_y];
                    uf->join(x, y);
                    if (d1 < d2) swap(d1, d2);
                    D[uf->find(x)] = (d1+1)/2 + max(1+(d2+1)/2, d1/2);
                }
            }
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
