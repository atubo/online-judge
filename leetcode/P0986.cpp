// https://leetcode.com/problems/interval-list-intersections/
// 986. Interval List Intersections

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"


class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A,
                                             vector<vector<int>>& B) {
        vector<vector<int>> ret;
        int m = A.size(), n = B.size();
        int p = 0, q = 0;
        while (p < m && q < n) {
            int l1 = A[p][0], r1 = A[p][1];
            int l2 = B[q][0], r2 = B[q][1];
            if (!((l2 > r1) || (r2 < l1))) {
                int l = max(l1, l2);
                int r = min(r1, r2);
                ret.push_back({l, r});
            }
            if (r1 < r2) p++;
            else q++;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
