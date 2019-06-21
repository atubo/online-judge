// https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
// 863. All Nodes Distance K in Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> ret;
        dfs(root, target, K, ret);
        return ret;
    }
private:
    int dfs(TreeNode* root, TreeNode* target, int K, vector<int> &ret) {
        if (root == target) {
            collect(root, K, ret);
            return 0;
        }
        int d;
        if (root->left && (d=dfs(root->left, target, K, ret)) >= 0) {
            if (d+1 == K) ret.push_back(root->val);
            else if (d+1 < K) collect(root->right, K-d-2, ret);
            return d+1;
        } else if (root->right && (d=dfs(root->right, target, K, ret)) >= 0) {
            if (d+1 == K) ret.push_back(root->val);
            else if (d+1 < K) collect(root->left, K-d-2, ret);
            return d+1;
        }
        return -1;
    }

    void collect(TreeNode* root, int K, vector<int> &ret) {
        if (!root) return;
        if (K == 0) {
            ret.push_back(root->val);
            return;
        }
        collect(root->left, K-1, ret);
        collect(root->right, K-1, ret);
    }
};

int main() {
    Solution solution;
    return 0;
}
