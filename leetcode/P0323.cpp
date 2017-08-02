// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/description/
// 323. Number of Connected Components in an Undirected Graph

#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    int countComponents(int N, vector<PII>& edges) {
        vector<vector<int>> adj(N);
        for (const auto& e: edges) {
            int u = e.first, v = e.second;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(N);
        int ret = 0;
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited);
                ret++;
            }
        }
        return ret;
    }

    void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
        visited[u] = true;
        for (int v: adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited);
            }
        }
    }
};

int main() {
    return 0;
}
