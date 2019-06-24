// https://leetcode.com/problems/merge-intervals/
// 56. Merge Intervals

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ret;
        if (intervals.empty()) return ret;
        int left = intervals[0][0], right = intervals[0][1];
        for (int i = 1; i < (int)intervals.size(); i++) {
            int l = intervals[i][0], r = intervals[i][1];
            if (l > right) {
                ret.push_back({left, right});
                left = l;
                right = r;
            } else {
                right = max(right, r);
            }
        }
        ret.push_back({left, right});
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
