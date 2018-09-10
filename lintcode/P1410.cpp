// https://www.lintcode.com/problem/matrix-water-injection/description
// 1410. Matrix Water Injection

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string waterInjection(vector<vector<int>> &matrix, int R, int C) {
        int DX[4] = {1, 0, -1, 0};
        int DY[4] = {0, 1, 0, -1};
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        vector<vector<bool>> vis(rows);
        for (int i = 0; i < rows; i++) {
            vis[i].resize(cols);
        }
        queue<pair<int, int>> q;
        q.push(make_pair(R, C));
        vis[R][C] = true;
        while (!q.empty()) {
            int x, y;
            tie(x, y) = q.front();
            q.pop();
            if (onBorder(x, y, rows, cols)) return "YES";
            for (int d = 0; d < 4; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2, rows, cols) &&
                    matrix[x2][y2] < matrix[x][y] &&
                    !vis[x2][y2]) {
                    q.push(make_pair(x2, y2));
                    vis[x2][y2] = true;
                }
            }
        }
        return "NO";
    }

    bool onBorder(int x, int y, int rows, int cols) {
        return x == 0 || x == rows-1 || y == 0 || y == cols-1;
    }

    bool inRange(int x, int y, int rows, int cols) {
        return 0 <= x && x < rows && 0 <= y && y < cols;
    }
};

int main() {
    Solution solution;
    return 0;
}
