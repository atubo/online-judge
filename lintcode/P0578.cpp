// https://www.lintcode.com/problem/lowest-common-ancestor-iii/description
// 578. Lowest Common Ancestor III

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode* lowestCommonAncestor3(TreeNode *root,
                                    TreeNode *A, TreeNode *B) {
        if (!root) return NULL;
        vector<TreeNode*> pa, pb;
        dfs(root, A, pa);
        dfs(root, B, pb);
        TreeNode *ret = NULL;
        size_t i = 0;
        while (i < pa.size() && i < pb.size() && pa[i] == pb[i]) {
            ret = pa[i];
            i++;
        }
        return ret;
    }

    bool dfs(TreeNode *node, TreeNode *target, vector<TreeNode*> &path) {
        path.push_back(node);
        if (node == target) return true;
        if (node->left && dfs(node->left, target, path)) return true;
        if (node->right && dfs(node->right, target, path)) return true;
        path.pop_back();
        return false;
    }
};

int main() {
    Solution solution;
    return 0;
}
