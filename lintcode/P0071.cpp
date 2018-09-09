// https://www.lintcode.com/problem/binary-tree-zigzag-level-order-traversal/description?_from=ladder&&fromId=23
// 71. Binary Tree Zigzag Level Order Traversal

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> ret;
        if (!root) return ret;
        bfs(root, ret);
        for (int i = 0; i < (int)ret.size(); i++) {
            if (i & 1) reverse(ret[i].begin(), ret[i].end());
        }
        return ret;
    }

    void bfs(TreeNode *root, vector<vector<int>> &ret) {
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 0));
        while (!q.empty()) {
            TreeNode *node;
            int d;
            tie(node, d) = q.front();
            q.pop();
            if (d > (int)ret.size()-1) ret.push_back(vector<int>());
            ret[d].push_back(node->val);
            if (node->left) {
                q.push(make_pair(node->left, d+1));
            }
            if (node->right) {
                q.push(make_pair(node->right, d+1));
            }
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
