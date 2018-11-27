// https://leetcode.com/problems/max-area-of-island/
// 695. Max Area of Island

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    const int DX[4] = {0, 1, 0, -1};
    const int DY[4] = {1, 0, -1, 0};
public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        const int n = grid.size();
        if (n == 0) return 0;
        const int m = grid[0].size();
        if (m == 0) return 0;
        vector<vector<bool>> vis(n);
        for (int i = 0; i < n; i++) vis[i].resize(m);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && grid[i][j]) {
                    ans = max(ans, bfs(grid, vis, i, j));
                }
            }
        }
        return ans;
    }

    bool inRange(int x, int y, int n, int m) {
        return 0 <= x && x < n && 0 <= y && y < m;
    }

    int bfs(const vector<vector<int>> &grid,
            vector<vector<bool>> &vis,
            int x, int y) {
        const int n = grid.size();
        const int m = grid[0].size();
        queue<pair<int, int>> q;
        q.push(make_pair(x, y));
        vis[x][y] = true;
        int ans = 0;
        while (!q.empty()) {
            tie(x, y) = q.front();
            ans++;
            q.pop();
            for (int d = 0; d < 4; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2, n, m) && grid[x2][y2] && !vis[x2][y2]) {
                    q.push(make_pair(x2, y2));
                    vis[x2][y2] = true;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
