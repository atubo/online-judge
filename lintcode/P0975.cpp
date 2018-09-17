// https://www.lintcode.com/problem/2-keys-keyboard/description
// 975. 2 Keys Keyboard

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int minSteps(int n) {
        vector<vector<int>> dp(n+1);
        for (int i = 1; i <= n; i++) dp[i].resize(n+1, INT_MAX);
        dp[1][1] = 1;
        for (int k = 1; k <= n; k++) {
            for (int l = k; l <= n; l++) {
                if (dp[l][k] == INT_MAX) continue;
                if (l+k <= n) dp[l+k][k] = min(dp[l+k][k], 1+dp[l][k]);
                if (k < l) dp[l][l] = min(dp[l][l], 1+dp[l][k]);
            }
        }
        int ans = INT_MAX;
        for (int i = 1; i <= n; i++) {
            ans = min(ans, dp[n][i]);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.minSteps(n) << endl;
    return 0;
}
