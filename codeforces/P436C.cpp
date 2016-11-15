// http://codeforces.com/problemset/problem/436/C
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

class Kruskal {
    using TIII = tuple<int, int, int>;  // (weight, u, v)
public:
    using Adj = vector<vector<int>>;
    static pair<Adj, int> mst(vector<TIII>& edges, int N) {
        Adj adj(N);
        UnionFind uf(N);
        sort(edges.begin(), edges.end());
        int total = 0;
        for (const TIII& e: edges) {
            int w, u, v;
            tie(w, u, v) = e;
            if (uf.find(u) == uf.find(v)) continue;
            adj[u].push_back(v);
            adj[v].push_back(u);
            uf.join(u, v);
            total += w;
        }
        return make_pair(adj, total);
    }
};

class Solution {
    using TIII = tuple<int, int, int>;
    using Adj = Kruskal::Adj;
private:
    int N, M, K, W;
    vector<string> levels;
public:
    Solution() {
        cin >> N >> M >> K >> W;
        levels.resize(K);
        for (int k = 0; k < K; k++) {
            for (int i = 0; i < N; i++) {
                string s;
                cin >> s;
                levels[k].append(s);
            }
        }
    }

    int dist(int p, int q) {
        const string& s = levels[p];
        const string& t = levels[q];
        int ret = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] != t[i]) ret += W;
        }
        return ret;
    }

    void solve() {
        vector<TIII> edges;
        vector<vector<int>> distMat(K, vector<int>(K, -1));

        for (int i = 0; i < K-1; i++) {
            for (int j = i+1; j < K; j++) {
                int d = min(N*M, dist(i, j));
                edges.push_back(make_tuple(d, i, j));
                distMat[i][j] = distMat[j][i] = d;
            }
        }

        auto mstResult = Kruskal::mst(edges, K);
        cout << mstResult.second + N*M << endl;

        bfs(mstResult.first, distMat);
    }

    void bfs(const Adj& adj, const vector<vector<int>>& distMat) {
        vector<bool> visited(K, false);
        queue<TIII> q;
        q.push(make_tuple(0, N*M, -1));
        visited[0] = true;
        while (!q.empty()) {
            int u, d, parent;
            tie(u, d, parent) = q.front();
            q.pop();
            if (d == N*M) {
                printf("%d %d\n", u+1, 0);
            } else {
                printf("%d %d\n", u+1, parent+1);
            }

            for (int v: adj[u]) {
                if (!visited[v]) {
                    q.push(make_tuple(v, distMat[u][v], u));
                    visited[v] = true;
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

