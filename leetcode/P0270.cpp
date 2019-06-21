// https://leetcode.com/problems/closest-binary-search-tree-value/
// 270. Closest Binary Search Tree Value
#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int ret = root->val;
        if (root->left && target < root->val) {
            int x = closestValue(root->left, target);
            if (fabs(target-root->val) > fabs(target-x)) ret = x;
        } else if (root->right && target > root->val) {
            int x = closestValue(root->right, target);
            if (fabs(target-root->val) > fabs(target-x)) ret = x;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
