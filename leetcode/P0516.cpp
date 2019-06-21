// https://leetcode.com/problems/longest-palindromic-subsequence/
// 516. Longest Palindromic Subsequence

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        const int n = s.length();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(s, 0, n-1, dp);
    }

    int solve(const string &s, int l, int r,
              vector<vector<int>> &dp) {
        if (l > r) return 0;
        if (l == r) return 1;
        if (dp[l][r] != -1) return dp[l][r];
        int &ret = dp[l][r] = 0;
        if (s[l] == s[r]) {
            return ret = 2 + solve(s, l+1, r-1, dp);
        }
        return ret = max(solve(s, l+1, r, dp), solve(s, l, r-1, dp));
    }
};

int main() {
    Solution solution;
    return 0;
}
