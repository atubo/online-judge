// https://leetcode.com/problems/graph-valid-tree/#/description
// 261. Graph Valid Tree

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if (n <= 0) return false;
        if ((int)edges.size() != n-1) return false;
        vector<vector<int>> adj(n);
        for (const PII& e: edges) {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
        }

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: adj[u]) {
                if (!visited[v]) {
                    q.push(v);
                    visited[v] = true;
                }
            }
        }

        int ret = true;
        for (bool v: visited) {
            if (!v) {
                ret = false;
                break;
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
