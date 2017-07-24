// https://leetcode.com/problems/walls-and-gates/#/description
// 286. Walls and Gates

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};

class Solution {
    using TIII = tuple<int, int, int>;
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        const int M = rooms.size();
        if (M == 0) return;
        const int N = rooms[0].size();
        if (N == 0) return;
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        queue<TIII> q;
        for (int r = 0; r < M; r++) {
            for (int c = 0; c < N; c++) {
                if (rooms[r][c] == 0) {
                    q.push(make_tuple(r, c, 0));
                    visited[r][c] = true;
                }
            }
        }

        while (!q.empty()) {
            int r, c, dist;
            tie(r, c, dist) = q.front();
            rooms[r][c] = dist;
            q.pop();
            for (int d = 0; d < 4; d++) {
                int u = r + DX[d];
                int v = c + DY[d];
                if (inRange(u, v, M, N) && rooms[u][v] != -1 &&
                    !visited[u][v]) {
                    q.push(make_tuple(u, v, dist+1));
                    visited[u][v] = true;
                }
            }
        }
    }

    bool inRange(int r, int c, int M, int N) {
        return 0 <= r && r < M && 0 <= c && c < N;
    }
};

int main() {
    Solution solution;
    return 0;
}
