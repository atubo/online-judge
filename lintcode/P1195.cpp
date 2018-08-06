// https://www.lintcode.com/problem/find-largest-value-in-each-tree-row/description
// 1195. Find Largest Value in Each Tree Row

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> largestValues(TreeNode *root) {
        vector<int> res;
        if (root) dfs(root, res, 0);
        return res;
    }

    void dfs(TreeNode *node, vector<int> &res, int d) {
        if (d > (int)res.size()-1) res.push_back(node->val);
        res[d] = max(res[d], node->val);
        if (node->left) dfs(node->left, res, d+1);
        if (node->right) dfs(node->right, res, d+1);
    }
};

int main() {
    Solution solution;
    TreeNode *root;
    cin >> root;
    printVector(solution.largestValues(root));
    return 0;
}
