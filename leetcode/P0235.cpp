// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/#/description
// 235. Lowest Common Ancestor of a Binary Search Tree

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        while (true) {
            if (p->val == curr->val || q->val == curr->val) break;
            if (p->val < curr->val && q->val < curr->val) curr = curr->left;
            else if (p->val > curr->val && q->val > curr->val) curr = curr->right;
            else break;
        }
        return curr;
    }
};

int main() {
    Solution solution;
    return 0;
}
