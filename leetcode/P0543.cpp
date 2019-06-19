// https://leetcode.com/problems/diameter-of-binary-tree/
// 543. Diameter of Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        auto ret = traverse(root);
        return ret.second;
    }

    pair<int, int> traverse(TreeNode* root) {
        if (!root) return make_pair(0, 0);
        int h1, d1, h2, d2;
        tie(h1, d1) = traverse(root->left);
        tie(h2, d2) = traverse(root->right);
        int h = 1 + max(h1, h2);
        int d = max(max(d1, d2), h1+h2);
        return make_pair(h, d);
    }
};

int main() {
    Solution solution;
    return 0;
}
