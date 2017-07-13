// https://leetcode.com/problems/invert-binary-tree/#/description
// 226. Invert Binary Tree

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        if (root->left) root->left = invertTree(root->left);
        if (root->right) root->right = invertTree(root->right);
        swap(root->left, root->right);
        return root;
    }
};

int main() {
    Solution solution;
    return 0;
}
