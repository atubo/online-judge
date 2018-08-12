// https://www.lintcode.com/problem/product-of-array-except-self/description
// 1310. Product of Array Except Self

#include <bits/stdc++.h>
using namespace std;

#include "../utils/Util.h"

class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        const int n = nums.size();
        vector<int> ret(n);
        if (n == 0) return ret;
        ret[0] = 1;
        for (int i = 1; i < n; i++) {
            ret[i] = ret[i-1] * nums[i-1];
        }
        int x = 1;
        for (int i = n-2; i >= 0; i--) {
            x *= nums[i+1];
            ret[i] *= x;
        }
        return ret;
    }
};

int main() {
    auto v = getVector();
    Solution solution;
    auto ret = solution.productExceptSelf(v);
    printVector(ret);
    return 0;
}
