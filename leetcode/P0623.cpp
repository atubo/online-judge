// https://leetcode.com/problems/add-one-row-to-tree/#/description
// 623. Add One Row to Tree

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v,  int d) {
        if (d == 1) {
            root = addLeft(root, v);
            return root;
        }
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 1));
        while (!q.empty()) {
            TreeNode *node;
            int depth;
            tie(node, depth) = q.front();
            q.pop();
            if (depth == d-1) {
                node->left = addLeft(node->left, v);
                node->right = addRight(node->right, v);
            } else {
                if (node->left) q.push(make_pair(node->left, depth+1));
                if (node->right) q.push(make_pair(node->right, depth+1));
            }
        }
        return root;
    }

    TreeNode* addLeft(TreeNode* left, int v) {
        TreeNode* node = new TreeNode(v);
        node->left = left;
        return node;
    }

    TreeNode* addRight(TreeNode* right, int v) {
        TreeNode* node = new TreeNode(v);
        node->right = right;
        return node;
    }
};

int main() {
    Solution solution;
    return 0;
}
