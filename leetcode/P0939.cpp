// https://leetcode.com/problems/minimum-area-rectangle/
// 939. Minimum Area Rectangle

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int minAreaRect(vector<vector<int>> &points) {
        map<int, vector<vector<int>>> byy;
        for (const auto &p: points) {
            byy[p[1]].push_back(p);
        }

        map<pair<int, int>, int> last;
        int ret = INT_MAX;
        for (auto it = byy.begin(); it != byy.end(); ++it) {
            int y = it->first;
            const auto pts = it->second;
            const int m = pts.size();
            for (int i = 0; i < m-1; i++) {
                for (int j = i+1; j < m; j++) {
                    int x1 = pts[i][0];
                    int x2 = pts[j][0];
                    if (x1 == x2) continue;
                    if (x1 > x2) swap(x1, x2);
                    pair<int, int> curr = make_pair(x1, x2);
                    if (last.find(curr) != last.end()) {
                        int yp = last[curr];
                        ret = min(ret, (y-yp)*(x2-x1));
                    }
                    last[curr] = y;
                }
            }
        }
        return ret == INT_MAX ? 0 : ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
