// https://leetcode.com/problems/subarray-sum-equals-k/
// 560. Subarray Sum Equals K
#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int subarraySum(vector<int> &nums, int k) {
        int ret = 0;
        int ps = 0;
        map<int, int> cnt;
        cnt[0] = 1;
        for (int i = 0; i < (int)nums.size(); i++) {
            ps += nums[i];
            if (cnt.find(ps-k) != cnt.end()) {
                ret += cnt[ps-k];
            }
            cnt[ps]++;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
