// https://leetcode.com/problems/find-right-interval/#/description
// 436. Find Right Interval

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval(): start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        vector<int> pts;
        for (const auto& i: intervals) {
            pts.push_back(i.start);
            pts.push_back(i.end);
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        const int N = pts.size();
        vector<int> p2i(N, -1);
        for (int i = 0; i < (int)intervals.size(); i++) {
            int idx = findIdx(pts,intervals[i].start);
            p2i[idx] = i;
        }

        vector<int> next(N, -1);
        vector<int> ret(intervals.size());
        for (int i = N-2; i >= 0; i--) {
            int idx = p2i[i];
            if (idx > -1) {
                int pos = findIdx(pts, intervals[idx].end);
                ret[idx] = next[pos];
                next[i] = idx;
            } else {
                next[i] = next[i+1];
            }
        }
        return ret;
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
    auto ret = solution.findRightInterval(A);
    printVector(ret);
    return 0;
}
