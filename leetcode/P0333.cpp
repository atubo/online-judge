// https://leetcode.com/problems/largest-bst-subtree/description/
// 333. Largest BST Subtree

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using Node = TreeNode;
    struct Result {
        Result(bool isBST_, int minVal_, int maxVal_, int maxSz_):
            isBST(isBST_), minVal(minVal_), maxVal(maxVal_), maxSz(maxSz_) {}
        bool isBST;
        int minVal, maxVal;
        int maxSz;
    };
public:
    int largestBSTSubtree(Node* root) {
        if (!root) return 0;
        Result* ret = traverse(root);
        return ret->maxSz;
    }

    Result* traverse(Node* node) {
        if (!node) return NULL;
        Result* left = traverse(node->left);
        Result* right = traverse(node->right);
        return merge(node, left, right);
    }

    Result* merge(Node* node, Result* left, Result* right) {
        if (left && right) {
            if (left->isBST && right->isBST &&
                left->maxVal < node->val && node->val < right->minVal) {
                return new Result(true, left->minVal, right->maxVal,
                                  left->maxSz + right->maxSz + 1);
            } else {
                return new Result(false, -1, -1, max(left->maxSz,
                                                     right->maxSz));
            }
        } else if (left) {
            if (left->isBST && left->maxVal < node->val) {
                return new Result(true, left->minVal, node->val,
                                  left->maxSz + 1);
            } else {
                return new Result(false, -1, -1, left->maxSz);
            }
        } else if (right) {
            if (right->isBST && node->val < right->minVal) {
                return new Result(true, node->val, right->maxVal,
                                  right->maxSz + 1);
            } else {
                return new Result(false, -1, -1, right->maxSz);
            }
        } else {
            return new Result(true, node->val, node->val, 1);
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
