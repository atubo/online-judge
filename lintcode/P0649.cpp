// https://www.lintcode.com/problem/binary-tree-upside-down/description
// 649. Binary Tree Upside Down

#include <bits/stdc++.h>
using namespace std;

#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode *upsideDownBinaryTree(TreeNode *root) {
        if (!root) return root;
        TreeNode *rt, *leaf;
        tie(rt, leaf) = dfs(root);
        return rt;
    }

    pair<TreeNode*, TreeNode*> dfs(TreeNode *node) {
        if (!node->left) return make_pair(node, node);
        TreeNode *rt, *leaf;
        tie(rt, leaf) = dfs(node->left);
        leaf->left = node->right;
        leaf->right = node;
        node->left = node->right = NULL;
        return make_pair(rt, node);
    }
};

int main() {
    Solution solution;
    TreeNode *root;
    cin >> root;
    root = solution.upsideDownBinaryTree(root);
    printTree(root);
    return 0;
}
