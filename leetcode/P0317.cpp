// https://leetcode.com/problems/shortest-distance-from-all-buildings/description/
// 317. Shortest Distance from All Buildings

#include <bits/stdc++.h>
using namespace std;

class Solution {
    using TIII = tuple<int, int, int>;
public:
    int shortestDistance(vector<vector<int>>& grid) {
        const int M = grid.size();
        const int N = grid[0].size();
        vector<vector<int>> dist(M, vector<int>(N));
        vector<vector<int>> cnt(M, vector<int>(N));
        int total = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 1) {
                    bfs(i, j, grid, dist, cnt);
                    total++;
                }
            }
        }

        int ret = INT_MAX;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0 && cnt[i][j] == total) {
                    ret = min(ret, dist[i][j]);
                }
            }
        }
        return ret == INT_MAX ? -1 : ret;
    }

    void bfs(int row, int col, const vector<vector<int>>& grid,
             vector<vector<int>>& dist,
             vector<vector<int>>& cnt) {
        const int DX[4] = {1, 0, -1, 0};
        const int DY[4] = {0, 1, 0, -1};
        const int M = grid.size();
        const int N = grid[0].size();
        vector<vector<bool>> visited(M, vector<bool>(N));
        queue<TIII> q;
        q.push(make_tuple(row, col, 0));
        visited[row][col] = true;
        while (!q.empty()) {
            int d;
            tie(row, col, d) = q.front();
            q.pop();
            dist[row][col] += d;
            cnt[row][col]++;
            for (int dir = 0; dir < 4; dir++) {
                int nr = row + DX[dir];
                int nc = col + DY[dir];
                if (inRange(nr, nc, M, N) &&
                    grid[nr][nc] == 0 && !visited[nr][nc]) {
                    q.push(make_tuple(nr, nc, d+1));
                    visited[nr][nc] = true;
                }
            }
        }
    }

    bool inRange(int i, int j, int M, int N) {
        return 0 <= i && i < M && 0 <= j && j < N;
    }
};

int main() {
    return 0;
}
