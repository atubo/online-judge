// https://leetcode.com/problems/new-21-game/description/
// 837. New 21 Game

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double new21Game(int N, int K, int W) {
        vector<double> dp(N+1);
        vector<double> ps(N+2);
        for (int i = N; i >= K; i--) {
            dp[i] = 1;
            ps[i] = dp[i] + ps[i+1];
        }
        for (int i = K-1; i >= 0; i--) {
            int r = min(N, i+W);
            dp[i] = ps[i+1] - ps[r+1];
            dp[i] /= W;
            ps[i] = dp[i] + ps[i+1];
        }
        return dp[0];
    }
};

int main() {
    int n, k, w;
    cin >> n >> k >> w;
    Solution solution;
    cout << solution.new21Game(n, k, w) << endl;
    return 0;
}
