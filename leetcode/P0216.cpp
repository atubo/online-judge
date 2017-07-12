// https://leetcode.com/problems/combination-sum-iii/#/description
// 216. Combination Sum III

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> curr;
        vector<vector<int>> ret;
        dfs(n, k, 1, curr, ret);
        return ret;
    }

    void dfs(int n, int k, int m, vector<int>& curr, vector<vector<int>>& ret) {
        if (k == 0) {
            if (n == 0) ret.push_back(curr);
            return;
        }
        if (m == 10) return;
        if (n >= m) {
            curr.push_back(m);
            dfs(n-m, k-1, m+1, curr, ret);
            curr.pop_back();
        }
        dfs(n, k, m+1, curr, ret);
    }
};

int main() {
    int k, n;
    cin >> k >> n;
    Solution solution;
    auto ret = solution.combinationSum3(k, n);
    for (const auto& v: ret) {
        printVector(v);
    }
    return 0;
}
