// https://www.lintcode.com/problem/digital-flip/description
// 843. Digital Flip

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int flipDigit(vector<int> &nums) {
        const int n = nums.size();
        if (n == 0) return 0;
        vector<int> dp0(n), dp1(n);
        dp0[n-1] = (nums[n-1] != 0);
        dp1[n-1] = (nums[n-1] != 1);
        for (int i = n-2; i >= 0; i--) {
            if (nums[i] == 1) {
                dp1[i] = min(dp1[i+1], dp0[i+1]);
                dp0[i] = 1 + dp0[i+1];
            } else {
                dp1[i] = 1 + min(dp1[i+1], dp0[i+1]);
                dp0[i] = dp0[i+1];
            }
        }
        return min(dp1[0], dp0[0]);
    }
};

int main() {
    Solution solution;
    return 0;
}
