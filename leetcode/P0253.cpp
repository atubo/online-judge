// https://leetcode.com/problems/meeting-rooms-ii/#/description
// 253. Meeting Rooms II

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
    Interval(int s, int e): start(s), end(e) {}
};

class Solution {
    using PII = pair<int, int>;
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<PII> pts;
        for (const auto& i: intervals) {
            pts.push_back(make_pair(i.start, 1));
            pts.push_back(make_pair(i.end, -1));
        }
        sort(pts.begin(), pts.end());
        int ret = 0, curr = 0;
        for (const PII& p: pts) {
            curr += p.second;
            ret = max(ret, curr);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
