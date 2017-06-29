// https://leetcode.com/problems/student-attendance-record-ii/#/description
// 552. Student Attendance Record II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int64_t add(int64_t a, int64_t b) {
        return (a + b) % 1000000007;
    }

    int64_t add3(int64_t a, int64_t b, int64_t c) {
        return add(add(a, b), c);
    }

    int checkRecord(int n) {
        if (n == 1) return 3;
        int dp[2][2][8];
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = dp[0][0][1] = dp[0][0][3] = dp[0][0][4] = 1;
        dp[0][1][2] = dp[0][1][5] = dp[0][1][6] = dp[0][1][7] = 1;

        int d = 0;
        for (int i = 3; i <= n; i++) {
            int p = d;
            d ^= 1;
            dp[d][0][0] = add(dp[p][0][0], dp[p][0][3]);
            dp[d][0][1] = add(dp[p][0][0], dp[p][0][3]);
            dp[d][0][3] = add(dp[p][0][1], dp[p][0][4]);
            dp[d][0][4] = dp[p][0][1];
            dp[d][1][2] = add(dp[p][0][0], dp[p][0][3]);
            dp[d][1][5] = add(dp[p][0][1], dp[p][0][4]);

            dp[d][1][0] = add3(dp[p][1][0], dp[p][1][3], dp[p][1][6]);
            dp[d][1][1] = add3(dp[p][1][0], dp[p][1][3], dp[p][1][6]);
            dp[d][1][3] = add3(dp[p][1][1], dp[p][1][4], dp[p][1][7]);
            dp[d][1][4] = add(dp[p][1][1], dp[p][1][7]);
            dp[d][1][6] = add(dp[p][1][2], dp[p][1][5]);
            dp[d][1][7] = add(dp[p][1][2], dp[p][1][5]);
        }
        int res = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                res = add(res, dp[d][i][j]);
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.checkRecord(n) << endl;
    return 0;
}
