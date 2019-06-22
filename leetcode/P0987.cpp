// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
// 987. Vertical Order Traversal of a Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    struct Data {
        int val, d;
        bool operator < (const Data &other) const {
            if (d != other.d) return d < other.d;
            return val < other.val;
        }
    };
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return vector<vector<int>>();
        int minx = findMinx(root, 0);
        int maxx = findMaxx(root, 0);
        vector<vector<Data>> holder(maxx-minx+1);
        queue<tuple<TreeNode*, int, int>> q;
        q.push({root, -minx, 0});
        while (!q.empty()) {
            TreeNode* curr;
            int x, d;
            tie(curr, x, d) = q.front();
            q.pop();
            holder[x].push_back({curr->val, d});
            if (curr->left) q.push({curr->left, x-1, d+1});
            if (curr->right) q.push({curr->right, x+1, d+1});
        }
        for (auto &v: holder) sort(v.begin(), v.end());
        vector<vector<int>> ret(maxx-minx+1);
        for (int i = 0; i <= maxx-minx; i++) {
            for (const auto &d: holder[i]) {
                ret[i].push_back(d.val);
            }
        }
        return ret;
    }

    int findMinx(TreeNode* root, int x) {
        int ret = x;
        if (root->left) ret = min(ret, findMinx(root->left, x-1));
        if (root->right) ret = min(ret, findMinx(root->right, x+1));
        return ret;
    }

    int findMaxx(TreeNode* root, int x) {
        int ret = x;
        if (root->left) ret = max(ret, findMaxx(root->left, x-1));
        if (root->right) ret = max(ret, findMaxx(root->right, x+1));
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
