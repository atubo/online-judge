// https://leetcode.com/problems/total-hamming-distance/
// 477. Total Hamming Distance

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int ret = 0;
        for (int i = 0; i < 31; i++) {
            ret += tally(nums, i);
        }
        return ret;
    }
private:
    int tally(const vector<int>& nums, int d) {
        const int n = nums.size();
        int cnt = 0;
        for (int x: nums) {
            cnt += (x >> d) & 1;
        }
        return (n-cnt)*cnt;
    }
};

int main() {
    Solution solution;
    return 0;
}
