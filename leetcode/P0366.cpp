// https://leetcode.com/problems/find-leaves-of-binary-tree/#/description
// 366. Find Leaves of Binary Tree

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> ret;
        dfs(root, ret);
        return ret;
    }

    int dfs(TreeNode* node, vector<vector<int>>& ret) {
        if (!node) return -1;
        int d = 1 + dfs(node->left, ret);
        d = max(d, 1 + dfs(node->right, ret));
        if (d == (int)ret.size()) ret.push_back({});
        ret[d].push_back(node->val);
        return d;
    }
};

int main() {
    Solution solution;
    return 0;
}
