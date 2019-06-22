// https://leetcode.com/problems/diagonal-traverse/
// 498. Diagonal Traverse

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        const int m = matrix.size();
        if (m == 0) return ret;
        const int n = matrix[0].size();
        if (n == 0) return ret;
        for (int d = 0; d < m + n - 1; d++) {
            if ((d & 1) == 0) {
                int x0 = d, y0 = 0;
                if (d > m-1) {
                    x0 = m - 1;
                    y0 = d - m + 1;
                }
                for (int t = 0; x0-t >= 0 && y0+t < n; t++) {
                    int x = x0 - t;
                    int y = y0 + t;
                    ret.push_back(matrix[x][y]);
                }
            } else {
                int x0 = 0, y0 = d;
                if (d > n-1) {
                    x0 = d - n + 1;
                    y0 = n - 1;
                }
                for (int t = 0; x0+t < m && y0-t >= 0; t++) {
                    int x = x0 + t;
                    int y = y0 - t;
                    ret.push_back(matrix[x][y]);
                }
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
