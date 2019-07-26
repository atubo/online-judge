// https://leetcode.com/problems/binary-tree-upside-down/
// 156. Binary Tree Upside Down

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root) return root;
        TreeNode *newroot, *leaf;
        tie(newroot, leaf) = build(root);
        return newroot;
    }

    pair<TreeNode*, TreeNode*> build(TreeNode* root) {
        if (!root->left) return make_pair(root, root);
        TreeNode *newroot, *leaf;
        tie(newroot, leaf) = build(root->left);
        leaf->left = root->right;
        leaf->right = root;
        root->left = root->right = NULL;
        return make_pair(newroot, root);
    }
};

int main() {
    Solution solution;
    return 0;
}
