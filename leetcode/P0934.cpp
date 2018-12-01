// https://leetcode.com/problems/shortest-bridge/
// 934. Shortest Bridge

#include <bits/stdc++.h>
using namespace std;
#include "../utils/Util.h"

class Solution {
    const int DX[4] = {0, 1, 0, -1};
    const int DY[4] = {1, 0, -1, 0};
public:
    int shortestBridge(vector<vector<int>> &A) {
        const int n = A.size();
        const int m = A[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m));
        queue<tuple<int, int, int>> q;
        for (int i = 0; i < n; i++) {
            bool done = false;
            for (int j = 0; j < m; j++) {
                if (A[i][j]) {
                    fillQueue(A, q, i, j, vis);
                    done = true;
                    break;
                }
            }
            if (done) break;
        }
        while (!q.empty()) {
            int x, y, d;
            tie(x, y, d) = q.front();
            q.pop();
            for (int dir = 0; dir < 4; dir++) {
                int x2 = x + DX[dir];
                int y2 = y + DY[dir];
                if (!inRange(x2, y2, n, m)) continue;
                if (!vis[x2][y2]) {
                    if (A[x2][y2]) {
                        return d;
                    } else {
                        vis[x2][y2] = true;
                        q.push({x2, y2, d+1});
                    }
                }
            }
        }
        return -1;
    }
private:
    void fillQueue(const vector<vector<int>> &A,
                   queue<tuple<int, int, int>> &q,
                   int x, int y, vector<vector<bool>> &vis) {
        const int n = A.size();
        const int m = A[0].size();
        vis[x][y] = true;
        q.push({x, y, 0});
        for (int d = 0; d < 4; d++) {
            int x2 = x + DX[d];
            int y2 = y + DY[d];
            if (inRange(x2, y2, n, m) && !vis[x2][y2] && A[x2][y2]) {
                fillQueue(A, q, x2, y2, vis);
            }
        }
    }

    bool inRange(int x, int y, int n, int m) {
        return 0 <= x && x < n && 0 <= y && y < m;
    }
};

int main() {
    auto A = getMatrix();
    Solution solution;
    cout << solution.shortestBridge(A) << endl;
    return 0;
}
