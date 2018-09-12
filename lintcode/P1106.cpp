// https://www.lintcode.com/problem/maximum-binary-tree/description
// 1106. Maximum Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int> &nums) {
        return build(nums.begin(), nums.end());
    }

    TreeNode* build(vector<int>::const_iterator b,
                    vector<int>::const_iterator e) {
        if (b == e) return NULL;
        auto it = max_element(b, e);
        TreeNode *node = new TreeNode(*it);
        node->left = build(b, it);
        if (it != e) node->right = build(it+1, e);
        return node;
    }
};

int main() {
    Solution solution;
        
    return 0;
}
