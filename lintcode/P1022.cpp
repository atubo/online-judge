// https://www.lintcode.com/problem/valid-tic-tac-toe-state/description
// 1022. Valid Tic-Tac-Toe State

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool validTicTacToe(vector<string> &board) {
        int countx = count(board, 'X');
        int counto = count(board, 'O');
        if (!(countx == counto || countx == counto+1)) return false;
        int winx = calcWin(board, 'X');
        int wino = calcWin(board, 'O');
        if (winx + wino > 1) return false;
        if (wino == 1 && counto < countx) return false;
        if (winx == 1 && counto == countx) return false;
        return true;
    }

    int count(const vector<string> &board, char player) {
        int ans = 0;
        for (const auto &line: board) {
            for (char c: line) {
                ans += (c == player);
            }
        }
        return ans;
    }

    int calcWin(const vector<string> &board, char player) {
        vector<vector<int>> config = {
            {0, 0, 0, 1, 0, 2},
            {1, 0, 1, 1, 1, 2},
            {2, 0, 2, 1, 2, 2},
            {0, 0, 1, 0, 2, 0},
            {0, 1, 1, 1, 2, 1},
            {0, 2, 1, 2, 2, 2},
            {0, 0, 1, 1, 2, 2},
            {0, 2, 1, 1, 2, 0}
        };
        int ans = 0;
        for (const auto & cfg: config) {
            int cnt = 0;
            for (int i = 0; i < 3; i++) {
                int x = cfg[2*i], y = cfg[2*i+1];
                cnt += (board[x][y] == player);
            }
            ans += (cnt == 3);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
