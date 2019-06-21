// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
// 714. Best Time to Buy and Sell Stock with Transaction Fee

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int maxProfit(vector<int> &prices, int fee) {
        const int n = prices.size();
        int dp0Prev = 0, dp1Prev = -prices[0];
        for (int i = 1; i < n; i++) {
            int dp0 = max(dp0Prev, dp1Prev + prices[i] - fee);
            int dp1 = max(dp1Prev, dp0Prev - prices[i]);
            dp0Prev = dp0;
            dp1Prev = dp1;
        }
        return dp0Prev;
    }
};

int main() {
    Solution solution;
    return 0;
}
