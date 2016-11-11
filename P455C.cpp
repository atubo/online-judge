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
    using PII = pair<int, int>;
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
        for (int i = 0; i < M; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
            uf->join(a, b);
        }
        D.resize(N, -1);
    }

    PII bfs(int s) {
        vector<bool> visited(N, false);
        queue<PII> q;
        q.push(make_pair(0, s));
        visited[s] = true;
        PII last;
        while (!q.empty()) {
            int d, u;
            tie(d, u) = last = q.front();
            q.pop();
            for (int v: adj[u]) {
                if (!visited[v]) {
                    q.push(make_pair(d+1, v));
                    visited[v] = true;
                }
            }
        }
        return last;
    }

    int dia(int s) {
        PII p = bfs(s);
        p = bfs(p.second);
        return p.first;
    }

    void solve() {
        for (int i = 0; i < N; i++) {
            if (D[uf->find(i)] == -1) {
                D[uf->find(i)] = dia(i);
            }
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
                if (uf->find(x) != uf->find(y)) {
                    int d1 = D[uf->find(x)];
                    int d2 = D[uf->find(y)];
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
