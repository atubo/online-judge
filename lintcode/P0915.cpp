// https://www.lintcode.com/problem/inorder-predecessor-in-bst/description
// 915. Inorder Predecessor in BST

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode *inorderPredecessor(TreeNode *root, TreeNode *p) {
        if (p->left) {
            auto q = p->left;
            while (q->right) q = q->right;
            return q;
        }
        TreeNode *q = NULL, *it = root;
        while (it != p) {
            if (it->val > p->val) it = it->left;
            else {
                q = it;
                it = it->right;
            }
        }
        return q;
    }
};

int main() {
    Solution solution;
    return 0;
}
