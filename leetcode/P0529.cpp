// https://leetcode.com/problems/minesweeper/
// 529. Minesweeper

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board,
                                     vector<int> &click) {
        int x = click[0], y = click[1];
        auto ret = board;
        if (board[x][y] == 'M') {
            ret[x][y] = 'X';
            return ret;
        }
        dfs(ret, x, y);
        return ret;
    }

    void dfs(vector<vector<char>> &board, int x, int y) {
        static const int DX[8] = {0, 1, 1, 1, 0, -1, -1, -1};
        static const int DY[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        const int m = board.size();
        const int n = board[0].size();
        int cnt = 0;
        for (int d = 0; d < 8; d++) {
            int x2 = x + DX[d];
            int y2 = y + DY[d];
            if (!inRange(x2, y2, m, n)) continue;
            if (board[x2][y2] == 'M') cnt++;
        }
        if (cnt == 0) {
            board[x][y] = 'B';
            for (int d = 0; d < 8; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2, m, n) && board[x2][y2] == 'E') {
                    dfs(board, x2, y2);
                }
            }
        } else {
            board[x][y] = '0' + cnt;
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
