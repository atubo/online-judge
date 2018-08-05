// https://www.lintcode.com/problem/partition-to-k-equal-sum-subsets/description
// 836. Partition to K Equal Sum Subsets

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool partitiontoEqualSumSubsets(vector<int> &nums, int k) {
        const int n = nums.size();
        int tot = accumulate(nums.begin(), nums.end(), 0);
        if (tot % k != 0) return false;
        int mask = (1<<n) - 1;
        return isFeasible(nums, mask, k, tot/k);
    }
private:
    bool isFeasible(const vector<int> &nums, int mask, int k, int d) {
        if (k == 1) return true;
        for (int m = mask; m;) {
            m = (m-1) & mask;
            if (calc(nums, m) == (k-1) * d) {
                if (isFeasible(nums, m, k-1, d)) return true;
            }
        }
        return false;
    }

    int calc(const vector<int> &nums, int mask) {
        int ans = 0;
        for (int i = 0; i < 16; i++) {
            if ((mask >> i) & 1) ans += nums[i];
        }
        return ans;
    }
};

int main() {
    auto a = getVector();
    int k;
    cin >> k;
    Solution solution;
    cout << solution.partitiontoEqualSumSubsets(a, k) << endl;
    return 0;
}
