// https://leetcode.com/problems/path-sum-iii/
// 437. Path Sum III

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int pathSum(TreeNode *root, int sum) {
        if (!root) return 0;
        map<int, int> cnt = {{0, 1}};
        int ret = 0;
        dfs(root, sum, cnt, 0, ret);
        return ret;
    }

    void dfs(TreeNode *root, int sum,
             map<int, int> &cnt, int ps, int &ret) {
        ps += root->val;
        if (cnt.count(ps-sum) > 0) {
            ret += cnt.at(ps-sum);
        }
        cnt[ps]++;
        if (root->left) dfs(root->left, sum, cnt, ps, ret);
        if (root->right) dfs(root->right, sum, cnt, ps, ret);
        cnt[ps]--;
    }
};

int main() {
    int s;
    cin >> s;
    TreeNode *root;
    cin >> root;
    Solution solution;
    cout << solution.pathSum(root, s) << endl;
    return 0;
}
