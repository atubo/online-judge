// https://leetcode.com/problems/maximum-vacation-days/
// 568. Maximum Vacation Days

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int maxVacationDays(vector<vector<int>> &flights,
                        vector<vector<int>> &days) {
        const int N = flights.size();
        const int K = days[0].size();
        vector<vector<int>> dp(N);
        for (int i = 0; i < N; i++) dp[i].resize(K, -1);
        dp[0][0] = days[0][0];
        for (int u = 1; u < N; u++) {
            if (flights[0][u]) dp[u][0] = days[u][0];
        }
        for (int k = 0; k < K-1; k++) {
            for (int u = 0; u < N; u++) {
                if (dp[u][k] == -1) continue;
                dp[u][k+1] = max(dp[u][k+1], dp[u][k] + days[u][k+1]);
                for (int v = 0; v < N; v++) {
                    if (flights[u][v]) {
                        dp[v][k+1] = max(dp[v][k+1],
                                         dp[u][k] + days[v][k+1]);
                    }
                }
            }
        }
        int ans = 0;
        for (int u = 0; u < N; u++) {
            ans = max(ans, dp[u][K-1]);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
