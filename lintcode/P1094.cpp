// https://www.lintcode.com/problem/second-minimum-node-in-a-binary-tree/description
// 1094. Second Minimum Node In a Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int findSecondMinimumValue(TreeNode *root) {
        if (!root || !root->left ||
            root->left->val == root->right->val) return -1;
        int x;
        TreeNode *smaller;
        if (root->left->val < root->right->val) {
            smaller = root->left;
            x = root->right->val;
        } else {
            smaller = root->right;
            x = root->left->val;
        }
        int second = findSecondMinimumValue(smaller);
        if (second >= 0) return min(x, second);
        else return x;
    }
};

int main() {
    Solution solution;
    TreeNode *root;
    cin >> root;
    cout << solution.findSecondMinimumValue(root) << endl;
    return 0;
}
