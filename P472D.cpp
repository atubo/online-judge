// http://codeforces.com/problemset/problem/472/D
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
    using TIII = tuple<int, int, int>;
    using Adj = vector<vector<PII>>;
private:
    int N;
    vector<vector<int>> D;
    Adj adj;
public:
    Solution() {
        cin >> N;
        D.resize(N);
        for (int i = 0; i < N; i++) {
            D[i].resize(N);
            for (int j = 0; j < N; j++) {
                scanf("%d", &D[i][j]);
            }
        }
        adj.resize(N);
    }

    bool solve() {
        if (!check()) return false;

        build();
        return verify();
    }

    bool check() const {
        // check diagonal
        for (int i = 0; i < N; i++) {
            if (D[i][i] != 0) return false;
        }
        // check symmetry and positivity
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                if (D[i][j] == 0 || D[i][j] != D[j][i]) return false;
            }
        }
        return true;
    }

    void build() {
        vector<TIII> dst;
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                dst.push_back(make_tuple(D[i][j], i, j));
            }
        }
        sort(dst.begin(), dst.end());

        UnionFind uf(N);
        for (const TIII t: dst) {
            int d, u, v;
            tie(d, u, v) = t;
            if (uf.find(u) != uf.find(v)) {
                adj[u].push_back(make_pair(v, d));
                adj[v].push_back(make_pair(u, d));
                uf.join(u, v);
            }
        }
    }

    bool verify() const {
        for (int i = 0; i < N; i++) {
            if (!verifyStartPoint(i)) return false;
        }
        return true;
    }

    bool verifyStartPoint(int s) const {
        vector<bool> visited(N, false);
        queue<PII> q;
        q.push(make_pair(0, s));
        visited[s] = true;
        while (!q.empty()) {
            int d, u;
            tie(d, u) = q.front();
            q.pop();
            if (d != D[u][s]) return false;
            for (const PII& p: adj[u]) {
                int v, x;
                tie(v, x) = p;
                if (!visited[v]) {
                    q.push(make_pair(d+x, v));
                    visited[v] = true;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution solution;
    cout << (solution.solve() ? "YES" : "NO") << endl;
    return 0;
}
