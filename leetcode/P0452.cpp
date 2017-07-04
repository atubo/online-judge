// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/#/description
// 452. Minimum Number of Arrows to Burst Balloons

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& A) {
        if (A.empty()) return 0;
        vector<int> pts;
        for(const auto& pr: A) {
            pts.push_back(pr.first);
            pts.push_back(pr.second);
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        const int M = pts.size();
        vector<int> dp(M), left(M, -1);
        for (const auto& pr: A) {
            int l = lower_bound(pts.begin(), pts.end(), pr.first) - pts.begin();
            int r = lower_bound(pts.begin(), pts.end(), pr.second) - pts.begin();
            left[r] = max(left[r], l);
        }
        int ret = 0;
        dp[0] = 0;
        for (int i = 1; i < M; i++) {
            int l = left[i];
            dp[i] = max(dp[i-1], (l >= 0) + (l > 0 ? dp[l-1] : 0));
            ret = max(ret, dp[i]);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
