// https://www.lintcode.com/problem/house-robber/description
// 392. House Robber

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    long long houseRobber(vector<int> &A) {
        if (A.empty()) return 0;
        long long dp[2];
        dp[0] = 0; dp[1] = A[0];
        for (int i = 1; i < (int)A.size(); i++) {
            long long x0 = max(dp[0], dp[1]);
            long long x1 = A[i] + dp[0];
            dp[0] = x0;
            dp[1] = x1;
        }
        return max(dp[0], dp[1]);
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    printf("%lld\n", solution.houseRobber(A));
    return 0;
}
