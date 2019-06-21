// https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
// Construct Binary Search Tree from Preorder Traversal

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode* bstFromPreorder(vector<int> &preorder) {
        return build(preorder, 0, preorder.size()-1);
    }

    TreeNode* build(const vector<int> &A, int l, int r) {
        if (l > r) return NULL;
        TreeNode *root = new TreeNode(A[l]);
        int p = l+1;
        while (p <= r&& A[p] < A[l]) p++;
        root->left = build(A, l+1, p-1);
        root->right = build(A, p, r);
        return root;
    }

};

int main() {
    Solution solution;
    return 0;
}
