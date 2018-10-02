// https://www.lintcode.com/problem/number-pair-statistics/description
// 844. Number Pair Statistics

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

struct Point {
    int x, y;
};

class Solution {
public:
    int pairNumbers(vector<Point> &p) {
        int64_t ans = 0;
        int cnt[4] = {0};
        for (const auto &pt: p) {
            int idx = ((pt.x&1) << 1) |(pt.y&1);
            cnt[idx]++;
        }
        for (int i = 0; i < 4; i++) {
            ans += 1LL * cnt[i] * (cnt[i]-1) / 2;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
