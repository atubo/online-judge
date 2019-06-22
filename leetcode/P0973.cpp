// https://leetcode.com/problems/k-closest-points-to-origin/
// K Closest Points to Origin

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    struct Data {
        int x, y, d;
        bool operator < (const Data &other) const {
            if (d != other.d) return d < other.d;
            if (x != other.x) return x < other.x;
            return y < other.y;
        }
    };
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<Data> tmp;
        for (const auto &p: points) {
            int x = p[0], y = p[1];
            tmp.push_back({x, y, x*x+y*y});
        }
        sort(tmp.begin(), tmp.end());
        vector<vector<int>> ret;
        for (int i = 0; i < K; i++) {
            ret.push_back({tmp[i].x, tmp[i].y});
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
