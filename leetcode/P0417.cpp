// https://leetcode.com/problems/pacific-atlantic-water-flow/
// 417. Pacific Atlantic Water Flow

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    using PII = pair<int, int>;
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<vector<int>> ret;
        int m = matrix.size();
        if (m == 0) return ret;
        int n = matrix[0].size();
        if (n == 0) return ret;

        vector<vector<int>> vis(m, vector<int>(n, 0));
        flowPacific(matrix, vis);
        flowAtlantic(matrix, vis);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (vis[i][j] == 3) ret.push_back({i, j});
            }
        }
        return ret;
    }

    void flowPacific(const vector<vector<int>> &matrix,
                     vector<vector<int>> &vis) {
        static const int DX[4] = {0, 1, 0, -1};
        static const int DY[4] = {1, 0, -1, 0};
        int m = matrix.size();
        int n = matrix[0].size();
        queue<PII> q;
        for (int i = 0; i < m; i++) {
            q.push({i, 0});
            vis[i][0] = 1;
        }
        for (int i = 0; i < n; i++) {
            q.push({0, i});
            vis[0][i] = 1;
        }
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            for (int d = 0; d < 4; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2, m, n) && !vis[x2][y2] &&
                    matrix[x2][y2] >= matrix[x][y]) {
                    q.push({x2, y2});
                    vis[x2][y2] = 1;
                }
            }
        }
    }

    void flowAtlantic(const vector<vector<int>> &matrix,
                      vector<vector<int>> &vis) {
        static const int DX[4] = {0, 1, 0, -1};
        static const int DY[4] = {1, 0, -1, 0};
        int m = matrix.size();
        int n = matrix[0].size();
        queue<PII> q;
        for (int i = 0; i < m; i++) {
            q.push({i, n-1});
            vis[i][n-1] |= 2;
        }
        for (int i = 0; i < n; i++) {
            q.push({m-1, i});
            vis[m-1][i] |= 2;
        }
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            for (int d = 0; d < 4; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2, m, n) && !(vis[x2][y2]&2) &&
                    matrix[x2][y2] >= matrix[x][y]) {
                    q.push({x2, y2});
                    vis[x2][y2] |= 2;
                }
            }
        }
    }

    bool inRange(int x, int y, int m, int n) {
        return 0 <= x && x < m && 0 <= y && y < n;
    }
};

int main() {
    Solution solution;
    return 0;
}
