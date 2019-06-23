// https://leetcode.com/problems/trapping-rain-water/
// 42. Trapping Rain Water

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int trap(vector<int>& height) {
        const int n = height.size();
        if (n == 0) return 0;
        vector<int> left(n), right(n);
        left[0] = height[0];
        for (int i = 1; i < n; i++) {
            left[i] = max(left[i-1], height[i]);
        }
        right[n-1] = height[n-1];
        for (int i = n-2; i >= 0; i--) {
            right[i] = max(right[i+1], height[i]);
        }

        int ret = 0;
        for (int i = 1; i < n-1; i++) {
            int h = min(left[i-1], right[i+1]);
            ret += max(0, h-height[i]);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
