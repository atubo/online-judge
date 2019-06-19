// https://leetcode.com/problems/check-completeness-of-a-binary-tree/
// 958. Check Completeness of a Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        auto ret = traverse(root);
        return ret.second != 2;
    }

    pair<int, int> traverse(TreeNode* root) {
        if (!root) return make_pair(0, 0);
        int d1, f1, d2, f2;
        tie(d1, f1) = traverse(root->left);
        tie(d2, f2) = traverse(root->right);
        if (d1 < d2) return make_pair(1+d2, 2);
        if (f1 == 2 || f2 == 2) return make_pair(1+max(d1, d2), 2);
        if (d2 < d1-1) return make_pair(1+d1, 2);
        int d = 1 + d1;
        if (f1 == 0) {
            if (d2 == d1) return make_pair(d, f2);
            return make_pair(d, f2==1 ? 2 : 1);
        } else {
            if (d2 == d1-1 && f2 == 0) return make_pair(d, 1);
            return make_pair(d, 2);
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
