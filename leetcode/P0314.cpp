// https://leetcode.com/problems/binary-tree-vertical-order-traversal/description/
// 314. Binary Tree Vertical Order Traversal

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using Node = TreeNode;
public:
    vector<vector<int>> verticalOrder(Node* root) {
        if (!root) return vector<vector<int>>();

        map<int, vector<int>> cols;
        bfs(root, cols);
        vector<vector<int>> ret;
        for (const auto& col: cols) {
            ret.push_back(col.second);
        }
        return ret;
    }

    void bfs(Node* root, map<int, vector<int>>& m) {
        queue<pair<Node*, int>> q;
        q.push(make_pair(root, 0));
        while (!q.empty()) {
            Node* node;
            int col;
            tie(node, col) = q.front();
            q.pop();
            m[col].push_back(node->val);
            if (node->left) q.push(make_pair(node->left, col-1));
            if (node->right) q.push(make_pair(node->right, col+1));
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
