// https://www.lintcode.com/problem/factorization/description
// 652. Factorization

#include <bits/stdc++.h>
using namespace std;
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> ret = dfs(n, 2);
        ret.pop_back();
        for (auto &v: ret) reverse(v.begin(), v.end());
        return ret;
    }

    vector<vector<int>> dfs(int n, int start) {
        vector<vector<int>> ret;
        for (int64_t i = start; i*i <= n; i++) {
            if (n % i == 0) {
                auto suffix = dfs(n/i, i);
                for (auto &v: suffix) v.push_back(i);
                copy(suffix.begin(), suffix.end(), back_inserter(ret));
            }
        }
        ret.push_back({n});
        return ret;
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
