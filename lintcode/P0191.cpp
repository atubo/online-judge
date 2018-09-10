// https://www.lintcode.com/problem/maximum-product-subarray/description
// 191. Maximum Product Subarray

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int maxProduct(vector<int> &nums) {
        const int n = nums.size();
        if (n == 1) return nums[0];
        int ret = 0;
        int p = 0;
        while (true) {
            while (p < n && nums[p] == 0) p++;
            if (p >= n) break;
            int q = p + 1;
            while (q < n && nums[q] != 0) q++;
            ret = max(ret, solve(nums, p, q));
            p = q;
        }
        return ret;
    }

    int solve(const vector<int> &nums, int p, int q) {
        if (q - p == 1) return nums[p];
        int first, last;
        int cnt = countNegative(nums, p, q, first, last);
        int ret;
        if (cnt & 1) {
            ret = max(calcProd(nums, p, last-1), calcProd(nums, first+1, q-1));
        } else {
            ret = calcProd(nums, p, q-1);
        }
        return ret;
    }

    int countNegative(const vector<int> &nums, int p, int q,
                      int &first, int &last) {
        first = -1;
        int cnt = 0;
        for (int i = p; i < q; i++) {
            if (nums[i] < 0) {
                last = i;
                if (first == -1) first = i;
                cnt++;
            }
        }
        return cnt;
    }

    int calcProd(const vector<int> &nums, int p, int q) {
        if (q < p) return -1;
        int ret = nums[p];
        for (int i = p+1; i <= q; i++) {
            ret *= nums[i];
        }
        return ret;
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    cout << solution.maxProduct(A) << endl;
    return 0;
}
