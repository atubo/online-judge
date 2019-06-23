// https://leetcode.com/problems/binary-tree-maximum-path-sum/
// 124. Binary Tree Maximum Path Sum

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        auto ret = solve(root);
        return ret.second;
    }

    pair<int,int> solve(TreeNode* root) {
        if (!root->left && !root->right) {
            return {root->val, root->val};
        }
        if (!root->left) {
            auto right = solve(root->right);
            int p = root->val + max(0, right.first);
            return {p, max(right.second, p)};
        }
        if (!root->right) {
            auto left = solve(root->left);
            int p = root->val + max(0, left.first);
            return {p, max(left.second, p)};
        }
        auto left = solve(root->left);
        auto right = solve(root->right);
        int p = root->val + max(0, max(left.first, right.first));
        int q = root->val + max(0, left.first) + max(0, right.first);
        return {p, max(max(left.second, right.second), q)};
    }
};

int main() {
    Solution solution;
    return 0;
}
