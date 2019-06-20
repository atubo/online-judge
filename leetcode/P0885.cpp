// https://leetcode.com/problems/spiral-matrix-iii/
// 885. Spiral Matrix III

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        vector<vector<int>> ret;
        ret.push_back({r0, c0});
        int r = r0, c = c0;
        int s = 1;
        while ((int)ret.size() < R*C) {
            tie(r, c) = move(0, s, r, c, R, C, ret);
            tie(r, c) = move(1, s, r, c, R, C, ret);
            tie(r, c) = move(2, s+1, r, c, R, C, ret);
            tie(r, c) = move(3, s+1, r, c, R, C, ret);
            s += 2;
        }
        return ret;
    }
private:
    pair<int, int> move(int dir, int s, int r, int c, int R, int C,
                        vector<vector<int>> &ret) {
        static int DX[4] = {0, 1, 0, -1};
        static int DY[4] = {1, 0, -1, 0};
        for (int i = 1; i <= s; i++) {
            int r2 = r + DX[dir]*i;
            int c2 = c + DY[dir]*i;
            if (inRange(r2, c2, R, C)) ret.push_back({r2, c2});
        }
        return make_pair(r+DX[dir]*s, c+DY[dir]*s);
    }

    bool inRange(int r, int c, int R, int C) {
        return 0 <= r && r < R && 0 <= c && c < C;
    }
};

int main() {
    Solution solution;
    solution.spiralMatrixIII(5, 6, 1, 4);
    return 0;
}
