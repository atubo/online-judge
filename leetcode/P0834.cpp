// https://leetcode.com/problems/sum-of-distances-in-tree/description/
// 834. Sum of Distances in Tree

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Solution {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>> &edges) {
        vector<vector<int>> adj(N);
        for (const auto &e: edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> sz(N), dist(N), ans(N);
        dfs1(adj, 0, 0, sz, dist);
        ans[0] = dist[0];
        dfs2(adj, 0, 0, sz, ans);
        return ans;
    }

    void dfs1(const vector<vector<int>> &adj, int u, int fa,
              vector<int> &sz, vector<int> &dist) {
        sz[u] = 1;
        for (int v: adj[u]) {
            if (v != fa) {
                dfs1(adj, v, u, sz, dist);
                sz[u] += sz[v];
                dist[u] += dist[v] + sz[v];
            }
        }
    }

    void dfs2(const vector<vector<int>> &adj, int u, int fa,
              const vector<int> &sz, vector<int> &ans) {
        const int N = adj.size();
        if (u != 0) {
            ans[u] = ans[fa] + N - 2*sz[u];
        }
        for (int v: adj[u]) {
            if (v != fa) {
                dfs2(adj, v, u, sz, ans);
            }
        }
    }
};

int main() {
    auto edges = getMatrix();
    Solution solution;
    auto ret = solution.sumOfDistancesInTree(edges.size(), edges);
    printVector(ret);
    return 0;
}
