// https://www.lintcode.com/problem/dungeon-game/description
// 1346. Dungeon Game

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>> &dungeon) {
        const int n = dungeon.size();
        if (n == 0) return 0;
        const int m = dungeon[0].size();
        if (m == 0) return 0;
        vector<vector<int>> dp(n);
        for (int i = 0; i < n; i++) dp[i].resize(m);
        dp[n-1][m-1] = 1;
        for (int i = m-2; i >= 0; i--) {
            dp[n-1][i] = max(1, dp[n-1][i+1] - dungeon[n-1][i+1]);
        }
        for (int i = n-2; i >= 0; i--) {
            dp[i][m-1] = max(1, dp[i+1][m-1] - dungeon[i+1][m-1]);
        }
        for (int i = n-2; i >= 0; i--) {
            for (int j = m-2; j >= 0; j--) {
                dp[i][j] = min(max(1, dp[i][j+1] - dungeon[i][j+1]),
                               max(1, dp[i+1][j] - dungeon[i+1][j]));
            }
        }
        return max(1, dp[0][0] - dungeon[0][0]);
    }
};

int main() {
    Solution solution;
    return 0;
}
