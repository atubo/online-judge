// https://leetcode.com/problems/closest-binary-search-tree-value-ii/
// 272. Closest Binary Search Tree Value II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        const double EPS = 1e-10;
        vector<int> ret;
        int xmin = getmin(root);
        int xmax = getmax(root);
        if (target > xmax) {
            dfs3(root, k, ret);
            return ret;
        }
        if (target < xmin) {
            dfs4(root, k, ret);
            return ret;
        }
        double hi = max(fabs(xmin-target), fabs(xmax-target));
        double lo = 0;

        int n = 0;
        auto ok = dfs(root, int(ceil(target-hi)), target+hi, n, k);
        if (ok && n == k) {
            dfs2(root, int(ceil(target-hi)), target+hi, ret);
            return ret;
        }


        while (lo < hi-EPS) {
            double mid = (lo + hi) / 2;
            n = 0;
            ok = dfs(root, int(ceil(target-mid)), target+mid, n, k);
            if (!ok) hi = mid;
            else lo = mid;
        }

        dfs2(root, int(ceil(target-lo)), target+lo, ret);
        return ret;
    }

    void dfs3(TreeNode* node, int k, vector<int> &ret) {
        if (node->right) dfs3(node->right, k, ret);
        if ((int)ret.size() < k) ret.push_back(node->val);
        if ((int)ret.size() < k && node->left) dfs3(node->left, k, ret);
    }

    void dfs4(TreeNode* node, int k, vector<int> &ret) {
        if (node->left) dfs4(node->left, k, ret);
        if ((int)ret.size() < k) ret.push_back(node->val);
        if ((int)ret.size() < k && node->right) dfs4(node->right, k, ret);
    }

    void dfs2(TreeNode* node, int lo, int hi, vector<int> &ret) {
        if (lo <= node->val && node->val <= hi) ret.push_back(node->val);
        if (node->val >= lo && node->left) {
            dfs2(node->left, lo, hi, ret);
        }
        if (node->val <= hi && node->right) {
            dfs2(node->right, lo, hi, ret);
        }
    }

    bool dfs(TreeNode* node, int lo, int hi, int &n, int k) {
        if (lo > hi) return true;
        if (lo <= node->val && node->val <= hi) n++;
        if (n > k) return false;
        if (node->val >= lo && node->left) {
            auto ok = dfs(node->left, lo, hi, n, k);
            if (!ok) return false;
        }
        if (node->val <= hi && node->right) {
            auto ok = dfs(node->right, lo, hi, n, k);
            if (!ok) return false;
        }
        return true;
    }

    int getmin(TreeNode* root) {
        auto node = root;
        while (node->left) node = node->left;
        return node->val;
    }

    int getmax(TreeNode* root) {
        auto node = root;
        while (node->right) node = node->right;
        return node->val;
    }
};

int main() {
    Solution solution;
    return 0;
}
