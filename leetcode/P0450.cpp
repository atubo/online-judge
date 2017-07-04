// https://leetcode.com/problems/delete-node-in-a-bst/#/description
// 450. Delete Node in a BST

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;
        TreeNode** fp = &root;
        while (*fp && (*fp)->val != key) {
            if ((*fp)->val < key) fp = &((*fp)->right);
            else fp = &((*fp)->left);
        }
        if (*fp == NULL) return root;
        if ((*fp)->left == NULL) {
            *fp = (*fp)->right;
        }
        else if ((*fp)->right == NULL) {
            *fp = (*fp)->left;
        } else {
            TreeNode* p = pred((*fp)->left);
            p->right = (*fp)->right;
            *fp = (*fp)->left;
        }
        return root;
    }

    TreeNode* pred(TreeNode* node) {
        TreeNode* p = node;
        while (p->right) {
            p = p->right;
        }
        return p;
    }
};

int main() {
    Solution solution;
    return 0;
}
