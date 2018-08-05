// https://www.lintcode.com/problem/merge-intervals/description
// 156. Merge Intervals

#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"
#include "../utils/Interval.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const Interval &a, const Interval &b) -> bool
             {return a.start < b.start;});
        vector<Interval> res;
        const int n = intervals.size();
        int p = 0;
        while (p < n) {
            int s = intervals[p].start;
            int e = intervals[p].end;
            int q = p + 1;
            while (q < n && intervals[q].start <= e) {
                e = max(e, intervals[q].end);
                q++;
            }
            res.push_back({s, e});
            p = q;
        }
        return res;
    }
};

int main() {
    Solution solution;
    vector<Interval> intervals;
    cin >> intervals;
    cout << solution.merge(intervals) << endl;
    return 0;
}
