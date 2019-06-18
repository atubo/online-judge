// https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/
// 426. Convert Binary Search Tree to Sorted Doubly Linked List

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node *root) {
        if (!root) return NULL;
        Node *b1 = treeToDoublyList(root->left);
        Node *b2 = treeToDoublyList(root->right);
        if (b1 && b2) {
            Node *e1 = b1->left;
            Node *e2 = b2->left;
            e1->right = root;
            root->left = e1;
            root->right = b2;
            b2->left = root;
            e2->right = b1;
            b1->left = e2;
            return b1;
        } else if (b1) {
            Node *e1 = b1->left;
            e1->right = root;
            root->left = e1;
            root->right = b1;
            b1->left = root;
            return b1;
        } else if (b2) {
            Node *e2 = b2->left;
            root->right = b2;
            b2->left = root;
            e2->right = root;
            root->left = e2;
            return root;
        } else {
            root->left = root->right = root;
            return root;
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
