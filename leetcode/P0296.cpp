// https://leetcode.com/problems/best-meeting-point/tabs/description
// 296. Best Meeting Point

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<PII> pts;
        vector<int> horz, vert;
        const int M = grid.size();
        if (M == 0) return 0;
        const int N = grid[0].size();
        if (N == 0) return 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j]) {
                    horz.push_back(j);
                    vert.push_back(i);
                    pts.push_back(make_pair(i, j));
                }
            }
        }
        const int K = pts.size();
        sort(horz.begin(), horz.end());
        sort(vert.begin(), vert.end());
        const int r = vert[K/2];
        const int c = horz[K/2];
        int ret = 0;
        for (const PII& pt: pts) {
            ret += abs(pt.first - r) + abs(pt.second - c);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
