// https://leetcode.com/problems/target-sum/
// 494. Target Sum

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int findTargetSumWays(vector<int> &nums, int S) {
        const int n = nums.size();
        vector<int> ps(n+1);
        for (int i = n-1; i >= 0; i--) {
            ps[i] = nums[i] + ps[i+1];
        }
        vector<vector<int>> dp(n, vector<int>(2*ps[0]+1, -1));
        return solve(nums, 0, S, dp, ps);
    }

    int solve(const vector<int> &A, int d, int S,
              vector<vector<int>> &dp,
              const vector<int> &ps) {
        const int n = A.size();
        if (d == n) return (S == 0);
        if (S > ps[0] || S < -ps[0]) return 0;
        if (dp[d][S+ps[0]] != -1) return dp[d][S+ps[0]];
        int &ret = dp[d][S+ps[0]] = 0;
        return ret = solve(A, d+1, S-A[d], dp, ps) +
            solve(A, d+1, S+A[d], dp, ps);
    }
};

int main() {
    Solution solution;
    vector<int> nums = {1, 1, 1, 1, 1};
    cout << solution.findTargetSumWays(nums, 3) << endl;
    return 0;
}
