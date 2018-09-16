// https://www.lintcode.com/problem/find-bottom-left-tree-value/description
// 1197. Find Bottom Left Tree Value

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int findBottomLeftValue(TreeNode *root) {
        return bfs(root);
    }

    int bfs(TreeNode *root) {
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 0));
        int curr = -1;
        int ans = -1;
        while (!q.empty()) {
            TreeNode *node;
            int d;
            tie(node, d) = q.front();
            q.pop();
            if (d > curr) {
                curr = d;
                ans = node->val;
            }
            if (node->left) {
                q.push(make_pair(node->left, d+1));
            }
            if (node->right) {
                q.push(make_pair(node->right, d+1));
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
