// https://leetcode.com/problems/inorder-successor-in-bst/#/description
// 285. Inorder Successor in BST

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using Node = TreeNode;
public:
    Node* inorderSuccessor(Node* root, Node* p) {
        if (p->right) return succ(p);
        Node* curr = root;
        Node* last = NULL;
        while (curr != p) {
            if (curr->val < p->val) curr = curr->right;
            else {
                last = curr;
                curr = curr->left;
            }
        }
        return last;
    }

    Node* succ(Node* node) {
        node = node->right;
        while (node->left) node = node->left;
        return node;
    }
};

int main() {
    Solution solution;
    return 0;
}
