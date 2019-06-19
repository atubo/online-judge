// https://leetcode.com/problems/continuous-subarray-sum/
// 523. Continuous Subarray Sum

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool checkSubarraySum(vector<int> &nums, int k) {
        if (k == 0) return check0(nums);
        if (k < 0) k = -k;
        const int n = nums.size();
        bool ret = false;
        int ps = 0;
        set<int> seen;
        seen.insert(ps);
        for (int i = 1; i < n; i++) {
            int x = (ps + nums[i-1] + nums[i]) % k;
            if (seen.find(x) != seen.end()) {
                ret = true;
                break;
            }
            ps += nums[i-1];
            seen.insert(ps % k);
        }
        return ret;
    }

    bool check0(vector<int> &nums) {
        for (int i = 1; i < (int)nums.size(); i++) {
            if (nums[i-1] == 0 && nums[i] == 0) return true;
        }
        return false;
    }
};

int main() {
    Solution solution;
    auto nums = getBracketedIntVector();
    int k = 2147483640;
    cout << solution.checkSubarraySum(nums, k) << endl;
    return 0;
}
