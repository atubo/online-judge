// https://leetcode.com/problems/binary-tree-right-side-view/
// 199. Binary Tree Right Side View

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ret;
        if (!root) return ret;
        dfs(root,0, ret);
        return ret;
    }

    void dfs(TreeNode *root, int d, vector<int> &ret) {
        if ((int)ret.size() == d) ret.push_back(root->val);
        if (root->right) dfs(root->right, d+1, ret);
        if (root->left) dfs(root->left, d+1,ret);
    }
};

int main() {
    Solution solution;
    return 0;
}
