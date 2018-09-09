// https://www.lintcode.com/problem/lowest-common-ancestor-of-a-binary-tree/description?_from=ladder&&fromId=23
// 88. Lowest Common Ancestor of a Binary Tree
#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode* A, TreeNode *B) {
        vector<TreeNode*> pa = path(root, A);
        vector<TreeNode*> pb = path(root, B);
        return search(pa, pb);
    }

    vector<TreeNode*> path(TreeNode *root, TreeNode *node) {
        vector<TreeNode*> p;
        dfs(root, node, p);
        return p;
    }

    bool dfs(TreeNode *node, TreeNode *target, vector<TreeNode*> &p) {
        p.push_back(node);
        if (node == target) return true;
        if (node->left && dfs(node->left, target, p)) return true;
        if (node->right && dfs(node->right, target, p)) return true;
        p.pop_back();
        return false;
    }

    TreeNode* search(const vector<TreeNode*> &pa,
                     const vector<TreeNode*> &pb) {
        int n = min(pa.size(), pb.size());
        for (int i = n-1; i >= 0; i--) {
            if (pa[i] == pb[i]) return pa[i];
        }
        return NULL;
    }
};

int main() {
    Solution solution;
    return 0;
}
