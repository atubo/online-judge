// https://www.lintcode.com/problem/symmetric-tree/description
// 1360. Symmetric Tree

#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root) return true;
        return check(root->left, root->right);
    }

    bool check(TreeNode *t1, TreeNode *t2) {
        if (!t1 && !t2) return true;
        if (!t1 || !t2) return false;
        return (t1->val == t2->val && check(t1->left, t2->right) &&
                check(t1->right, t2->left));
    }
};

int main() {
    Solution solution;
    auto pre = getVector();
    auto in = getVector();
    TreeNode *root = buildTree(pre, in);
    cout << solution.isSymmetric(root) << endl;
    return 0;
}
