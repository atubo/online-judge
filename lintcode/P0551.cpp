// https://www.lintcode.com/problem/nested-list-weight-sum/description
// 551. Nested List Weight Sum

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"
#include "../utils/NestedInteger.h"

class Solution {
public:
    int depthSum(const vector<NestedInteger>& ni) {
        int ans = 0;
        for (const auto &x : ni) {
            ans += depthSum(x, 1);
        }
        return ans;
    }

    int depthSum(const NestedInteger &ni, int depth) {
        if (ni.isInteger()) return ni.getInteger() * depth;
        int ans = 0;
        for (const auto &x: ni.getList()) {
            ans += depthSum(x, depth+1);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    vector<NestedInteger> ni;
    cin >> ni;
    cout << ni;
    cout << solution.depthSum(ni) << endl;
    return 0;
}
