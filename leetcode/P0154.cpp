// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
// 154. Find Minimum in Rotated Sorted Array II

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        const int n = nums.size();
        int ret = nums[0];
        int p = 0, q = n-1;
        while (p < q && nums[p] == nums[q]) {
            p++;
        }
        if (p > q) return ret;
        if (p == q) return min(ret, nums[p]);
        if (nums[p] < nums[q]) return min(ret, nums[p]);
        while (p < q-1) {
            int mid = (p + q) / 2;
            if (nums[mid] > nums[q]) p = mid;
            else q = mid;
        }
        return min(ret, nums[q]);
    }
};

int main() {
    return 0;
}
