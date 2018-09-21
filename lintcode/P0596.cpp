// https://www.lintcode.com/problem/minimum-subtree/description
// 596. Minimum Subtree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode *findSubtree(TreeNode *root) {
        if (!root) return NULL;
        int mx = INT_MAX;
        TreeNode *ret = NULL;
        dfs(root, mx, ret);
        return ret;
    }

    int dfs(TreeNode *node, int &mx, TreeNode*& ret) {
        int val = node->val;
        if (node->left) val += dfs(node->left, mx, ret);
        if (node->right) val += dfs(node->right, mx, ret);
        if (val < mx) {
            mx = val;
            ret = node;
        }
        return val;
    }
};

int main() {
    Solution solution;
    return 0;
}
