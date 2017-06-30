// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/#/description
// 600. Non-negative Integers without Consecutive Ones

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findIntegers(int N) {
        int dmax = 31;
        for (; dmax >= 0; dmax--) {
            if (N >> dmax) break;
        }
        vector<vector<int>> dp(2, vector<int>(32, -1));
        return solve(N, 0, dmax-1, false, dp) + solve(N, 1, dmax-1, true, dp);
    }

    int solve(int N, int d, int n, bool bounded, vector<vector<int>>& dp) {
        if (n == -1) return 1;
        if (!bounded && dp[d][n] >= 0) return dp[d][n];
        if (bounded) {
            if (d == 0) {
                if (((N >> n) & 1) == 0) return solve(N, 0, n-1, true, dp);
                else return solve(N, 0, n-1, false, dp) + solve(N, 1, n-1, true, dp);
            } else {
                return solve(N, 0, n-1, !((N >> n) & 1), dp);
            }
        } else {
            int& ret = dp[d][n];
            if (d == 0) {
                ret = solve(N, 0, n-1, false, dp) + solve(N, 1, n-1, false, dp);
            } else {
                ret = solve(N, 0, n-1, false, dp);
            }
            return ret;
        }
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.findIntegers(n) << endl;
    return 0;
}
