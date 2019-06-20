// https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/
// Maximum Sum of 3 Non-Overlapping Subarrays

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<int> ps(n+1, 0);
        for (int i = n-1; i >= 0; i--) {
            ps[i] = nums[i] + ps[i+1];
        }

        vector<int> pos1(n), dp1(n);
        for (int i = 0; i <= n-k; i++) {
            if (i == 0) {
                dp1[i] = ps[i] - ps[i+k];
                pos1[i] = 0;
                continue;
            }
            int x = ps[i] - ps[i+k];
            if (x > dp1[i-1]) {
                dp1[i] = x;
                pos1[i] = i;
            } else {
                dp1[i] = dp1[i-1];
                pos1[i] = pos1[i-1];
            }
        }

        vector<int> pos2(n), dp2(n);
        for (int i = k; i <= n-k; i++) {
            if (i == k) {
                dp2[i] = ps[i] - ps[i+k] + dp1[0];
                pos2[i] = i;
                continue;
            }
            int x = ps[i] - ps[i+k] + dp1[i-k];
            if (x > dp2[i-1]) {
                dp2[i] = x;
                pos2[i] = i;
            } else {
                dp2[i] = dp2[i-1];
                pos2[i] = pos2[i-1];
            }
        }

        vector<int> pos3(n), dp3(n);
        for (int i = 2*k; i <= n-k; i++) {
            if (i == 2*k) {
                dp3[i] = ps[i] - ps[i+k] + dp2[k];
                pos3[i] = i;
                continue;
            }
            int x = ps[i] - ps[i+k] + dp2[i-k];
            if (x > dp3[i-1]) {
                dp3[i] = x;
                pos3[i] = i;
            } else {
                dp3[i] = dp3[i-1];
                pos3[i] = pos3[i-1];
            }
        }

        vector<int> ret = {pos1[pos2[pos3[n-k]-k]-k],
            pos2[pos3[n-k]-k], pos3[n-k]};
        return ret;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {1, 2, 1, 2, 6, 7, 5, 1};
    solution.maxSumOfThreeSubarrays(nums, 2);
    return 0;
}
