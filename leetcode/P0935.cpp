// https://leetcode.com/problems/knight-dialer/
// 935. Knight Dialer

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    static const int MOD = 1e9+7;
public:
    int knightDialer(int N) {
        vector<vector<int>> moves = {
            {4, 6},
            {6, 8},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            {},
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4}
        };
        vector<vector<int>> dp(N, vector<int>(10, -1));
        int ans = 0;
        for (int i = 0; i < 10; i++) {
            ans = (ans + solve(N-1, i, moves, dp)) % MOD;
        }
        return ans;
    }
private:
    int solve(int n, int p, const vector<vector<int>> &moves,
              vector<vector<int>> &dp) {
        if (n == 0) return 1;
        if (dp[n][p] != -1) return dp[n][p];
        int &ret = dp[n][p] = 0;
        for (int nxt: moves[p]) {
            ret = (ret + solve(n-1, nxt, moves, dp)) % MOD;
        }
        return ret;
    }

};

int main() {
    Solution solution;
    for (int i = 1; i <= 3; i++) {
        cout << solution.knightDialer(i) << endl;
    }
    return 0;
}
