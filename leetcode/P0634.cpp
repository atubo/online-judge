// https://leetcode.com/problems/find-the-derangement-of-an-array/#/description
// 634. Find the Derangement of An Array

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    static const int MOD = 1000000007;
public:
    int add(int64_t a, int64_t b) {
        return (a + b) % MOD;
    }

    int mul(int64_t a, int64_t b) {
        return (a * b) % MOD;
    }

    int findDerangement(int N) {
        vector<int> dp(N+1);
        dp[0] = 1;
        for (int n = 2; n <= N; n++) {
            dp[n] = mul(n-1, add(dp[n-2], dp[n-1]));
        }
        return dp[N];
    }
};

int main() {
    Solution solution;
    int N;
    cin >> N;
    cout << solution.findDerangement(N) << endl;
    return 0;
}
