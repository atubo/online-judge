// https://leetcode.com/problems/friend-circles/
// 547. Friend Circles

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int findCircleNum(vector<vector<int>> &M) {
        const int n = M.size();
        vector<bool> vis(n);
        int ret = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(M, vis, i);
                ret++;
            }
        }
        return ret;
    }

    void dfs(const vector<vector<int>> &M,
             vector<bool> &vis, int u) {
        const int n = M.size();
        vis[u] = true;
        for (int v = 0; v < n; v++) {
            if (M[u][v] && !vis[v]) dfs(M, vis, v);
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
