// https://leetcode.com/problems/2-keys-keyboard/description/
// 650. 2 Keys Keyboard

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n+1, -1);
        dp[1] = 0;
        solve(n, dp);
        return dp[n];
    }

    int solve(int n, vector<int>& dp) {
        if (dp[n] >= 0) return dp[n];
        int &ret = dp[n];
        ret = n;
        for (int i = 2; i <= n/2; i++) {
            if (n % i == 0) ret = min(ret, solve(i, dp) + n/i);
        }
        return ret;
    }
};

int main() {
    int n;
    cin >> n;
    Solution solution;
    cout << solution.minSteps(n) << endl;
    return 0;
}
