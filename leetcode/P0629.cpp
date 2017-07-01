// https://leetcode.com/problems/k-inverse-pairs-array/#/description
// 629. K Inverse Pairs Array

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    const static int64_t MOD = 1000000007;
public:
    int add(int64_t a, int64_t b) {
        return (a + b) % MOD;
    }

    int sub(int64_t a, int64_t b) {
        return (a + MOD - b) % MOD;
    }

    int kInversePairs(int N, int K) {
        vector<vector<int>> dp(2, vector<int>(K+1)), dpps(2, vector<int>(K+1));
        int d = 0;
        dp[d][0] = 1;
        partial_sum(dp[d].begin(), dp[d].end(), dpps[d].begin());
        for (int n = 2; n <= N; n++) {
            int p = d;
            d ^= 1;
            for (int k = 0; k <= K; k++) {
                int kmin = max(0, k - (n-1));
                int kmax = k;
                dp[d][k] = sub(dpps[p][kmax], kmin > 0 ? dpps[p][kmin-1] : 0);
                dpps[d][k] = add(dp[d][k], k > 0 ? dpps[d][k-1] : 0);
            }
        }

        return dp[d][K];
    }
};

int main() {
    Solution solution;
    int N, K;
    cin >> N >> K;
    cout << solution.kInversePairs(N, K) << endl;
    return 0;
}
