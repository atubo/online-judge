// https://leetcode.com/problems/boundary-of-binary-tree/
// 545. Boundary of Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> ret;
        if (!root) return ret;
        ret.push_back(root->val);
        if (!root->left && !root->right) return ret;
        if (root->left) buildLeftBoundary(root->left, ret);
        buildLeaves(root, ret);
        if (root->right) {
            int p = ret.size();
            buildRightBoundary(root->right, ret);
            reverse(ret.begin()+p, ret.end());
        }
        return ret;
    }

    void buildLeftBoundary(TreeNode* root, vector<int> &ret) {
        if (!root->left && !root->right) return;
        ret.push_back(root->val);
        if (root->left) buildLeftBoundary(root->left, ret);
        else buildLeftBoundary(root->right, ret);
    }

    void buildRightBoundary(TreeNode* root, vector<int> &ret) {
        if (!root->left && !root->right) return;
        ret.push_back(root->val);
        if (root->right) buildRightBoundary(root->right, ret);
        else buildRightBoundary(root->left, ret);
    }

    void buildLeaves(TreeNode* root, vector<int> &ret) {
        if (!root->left && !root->right) {
            ret.push_back(root->val);
            return;
        }
        if (root->left) buildLeaves(root->left, ret);
        if (root->right) buildLeaves(root->right, ret);
    }
};

int main() {
    Solution solution;
    return 0;
}
