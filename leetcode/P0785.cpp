// https://leetcode.com/problems/is-graph-bipartite/
// 785. Is Graph Bipartite?

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool isBipartite(vector<vector<int>> &graph) {
        const int n = graph.size();
        vector<int> color(n, -1);
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!dfs(graph, color, i, 0)) return false;
            }
        }
        return true;
    }
    
    bool dfs(const vector<vector<int>> &g, vector<int> &color, int u, int c) {
        color[u] = c;
        for (int v: g[u]) {
            if (color[v] != -1) {
                if (color[v] != 1-color[u]) return false;
            } else {
                if (!dfs(g, color, v, 1-c)) return false;
            }
        }
        return true;
    }
};

int main() {
    Solution solution;
    return 0;
}
