// https://leetcode.com/problems/average-of-levels-in-binary-tree/#/description
// 637. Average of Levels in Binary Tree

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int64_t, int64_t>;
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<PII> stat;
        dfs(root, 0, stat);
        vector<double> ret;
        for (const auto& p: stat) {
            ret.push_back((double)p.first/p.second);
        }
        return ret;
    }

    void dfs(TreeNode* node, int d, vector<PII>& stat) {
        if (d > (int)stat.size()-1) stat.resize(d+1);
        stat[d].first += node->val;
        stat[d].second++;
        if (node->left) dfs(node->left, d+1, stat);
        if (node->right) dfs(node->right, d+1, stat);
    }
};

int main() {
    Solution solution;
    return 0;
}
