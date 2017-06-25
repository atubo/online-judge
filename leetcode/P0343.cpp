// https://leetcode.com/problems/integer-break/
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <strings.h>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(59);
        dp[0] = dp[1] = 1;
        if (n == 2) return 1;
        if (n == 3) return 2;
        dp[2] = 2;
        dp[3] = 3;
        for (int i = 4; i <= n; i++) {
            dp[i] = max(2 * dp[i-2], 3 * dp[i-3]);
        }
        return dp[n];
    }
};

int main() {
    int n;
    cin >> n;
    Solution solution;
    cout << solution.integerBreak(n) << endl;
    return 0;
}
