// https://leetcode.com/problems/coin-change-2/
// 518. Coin Change 2

#include <bits/stdc++.h>
using namespace std;
#include "../utils/Util.h"

class Solution {
public:
    int change(int amount, vector<int> &coins) {
        vector<int> dp(amount+1);
        dp[0] = 1;
        for (int c: coins) {
            for (int i = 0; i <= amount-c; i++) {
                dp[i+c] += dp[i];
            }
        }
        return dp[amount];
    }
};

int main() {
    int amount;
    cin >> amount;
    vector<int> coins = getBracketedIntVector();
    Solution solution;
    cout << solution.change(amount, coins) << endl;
    return 0;
}
