// https://leetcode.com/problems/maximum-swap/
// 670. Maximum Swap

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        const int n = s.length();
        vector<pair<int, int>> dp(n);
        dp[n-1] = {s[n-1], n-1};
        for (int i = n-2; i >= 0; i--) {
            if (s[i] > dp[i+1].first) {
                dp[i] = {s[i], i};
            } else {
                dp[i] = dp[i+1];
            }
        }
        for (int i = 0; i < n-1; i++) {
            if (s[i] < dp[i+1].first) {
                swap(s[i], s[dp[i+1].second]);
                break;
            }
        }
        return stoi(s);
    }
};

int main() {
    Solution solution;
    return 0;
}
