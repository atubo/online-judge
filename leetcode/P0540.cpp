// https://leetcode.com/problems/single-element-in-a-sorted-array/
// 540. Single Element in a Sorted Array

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int singleNonDuplicate(vector<int> &nums) {
        const int n = nums.size();
        if (n == 1) return nums[0];
        if (nums[0] != nums[1]) return nums[0];
        if (nums[n-1] != nums[n-2]) return nums[n-1];
        int l = 0, r = (n-1)/2;
        while (l < r-1) {
            int mid = (l + r) / 2;
            if (nums[2*mid] == nums[2*mid+1]) l = mid;
            else r = mid;
        }
        return nums[2*r];
    }
};

int main() {
    Solution solution;
    return 0;
}
