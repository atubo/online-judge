#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int minCost(vector<vector<int>> &costs) {
        if (costs.empty()) return 0;
        const int n = costs.size();
        vector<vector<int>> dp(n);
        dp[0].resize(3);
        dp[0] = costs[0];
        for (int i = 1; i < n; i++) {
            dp[i].resize(3);
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0];
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1];
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2];
        }
        return min(min(dp[n-1][0], dp[n-1][1]), dp[n-1][2]);
    }
};

int main() {
    Solution solution;
    return 0;
}
