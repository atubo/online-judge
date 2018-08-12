// https://www.lintcode.com/problem/factor-combinations/description
// 1308. Factor Combinations

#include <bits/stdc++.h>
using namespace std;

#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> ans = dfs(n, 2);
        ans.pop_back();
        for (auto &v: ans) {
            reverse(v.begin(), v.end());
        }
        return ans;
    }

    vector<vector<int>> dfs(int n, int start) {
        vector<vector<int>> ans;
        for (int64_t x = start; x * x <= n; x++) {
            if (n % x == 0) {
                auto prefix = dfs(n/x, x);
                for (auto &v: prefix) {
                    v.push_back(x);
                }
                copy(prefix.begin(), prefix.end(), back_inserter(ans));
            }
        }
        ans.push_back({n});
        return ans;
    }
};

int main() {
    int x;
    cin >> x;
    Solution solution;
    auto ret = solution.getFactors(x);
    for (auto v: ret) {
        printVector(v);
    }
    return 0;
}
