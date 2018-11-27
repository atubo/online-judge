// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
// 698. Partition to K Equal Sum Subsets

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool canPartitionKSubsets(vector<int> &nums, int k) {
        int tot = accumulate(nums.begin(), nums.end(), 0);
        if (tot % k) return false;
        sort(nums.begin(), nums.end(), greater<int>());
        if (nums[0] > tot/k) return false;
        const int n = nums.size();
        int mask = (1<<n) - 1;
        return dfs(nums, mask, tot/k, tot/k, k);
    }

    bool dfs(const vector<int> &nums, int mask, int s, int s0, int rem) {
        if (mask == 0 && rem == 0) return true;
        const int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                if (nums[i] == s) {
                    mask &= ~(1U << i);
                    if (dfs(nums, mask, s0, s0, rem-1)) return true;
                    mask |= (1 << i);
                    return false;
                } else if (nums[i] < s) {
                    mask &= ~(1U << i);
                    if (dfs(nums, mask, s-nums[i], s0, rem)) return true;
                    mask |= (1 << i);
                }
            }
        }
        return false;
    }
};

int main() {
    auto v = getBracketedIntVector();
    int k;
    cin >> k;
    Solution solution;
    cout << solution.canPartitionKSubsets(v, k) << endl;
    return 0;
}
