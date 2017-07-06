// https://leetcode.com/problems/non-overlapping-intervals/#/description
// 435. Non-overlapping Intervals

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        vector<int> pts;
        for (const auto& it: intervals) {
            pts.push_back(it.start);
            pts.push_back(it.end);
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        const int M = pts.size();
        vector<int> left(M, -1);
        for (const auto& it: intervals) {
            int r = findIdx(pts, it.end);
            int l = findIdx(pts, it.start);
            left[r] = max(left[r], l);
        }

        vector<int> dp(M);
        int ret = 0;
        for (int i = 1; i < M; i++) {
            int l = left[i];
            dp[i] = max(dp[i-1], (l > -1) + dp[l]);
            ret = max(ret, dp[i]);
        }
        return intervals.size() - ret;
    }

    int findIdx(const vector<int>& pts, int x) {
        return lower_bound(pts.begin(), pts.end(), x) - pts.begin();
    }
};

int main() {
    int N;
    cin >> N;
    vector<Interval> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i].start >> A[i].end;
    }
    Solution solution;
    cout << solution.eraseOverlapIntervals(A) << endl;
    return 0;
}
