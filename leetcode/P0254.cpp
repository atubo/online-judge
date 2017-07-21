// https://leetcode.com/problems/factor-combinations/#/description
// 254. Factor Combinations

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> ret;
        vector<int> curr;
        solve(n, 2, curr, ret);
        return ret;
    }

    void solve(int n, int fmin, vector<int>& curr, vector<vector<int>>& ret) {
        if (n == 1) {
            if (curr.size() > 1) ret.push_back(curr);
            return;
        }

        for (int i = fmin; i <= n; i++) {
            if (n % i == 0) {
                curr.push_back(i);
                solve(n/i, i, curr, ret);
                curr.pop_back();
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    Solution solution;
    auto ret = solution.getFactors(n);
    for (auto v: ret) {
        printVector(v);
    }
    return 0;
}
