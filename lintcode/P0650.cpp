// https://www.lintcode.com/problem/find-leaves-of-binary-tree/description
// 650. Find Leaves of Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode *root) {
        vector<vector<int>> ret;
        dfs(root, ret);
        return ret;
    }

    int dfs(TreeNode *node, vector<vector<int>> &ret) {
        if (!node) return -1;
        int depth = dfs(node->left, ret) + 1;
        depth = max(depth, dfs(node->right, ret)+1);
        if ((int)ret.size() < depth+1) ret.push_back({});
        ret[depth].push_back(node->val);
        return depth;
    }
};

int main() {
    Solution solution;
    TreeNode *root;
    cin >> root;
    auto ret = solution.findLeaves(root);
    for (auto v: ret) {
        printVector(v);
    }
    return 0;
}
