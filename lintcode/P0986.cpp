// https://www.lintcode.com/problem/battleships-in-a-board/description
// 986. Battleships in a Board

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int countBattleships(vector<vector<char>> &board) {
        const int n = board.size();
        if (n == 0) return 0;
        const int m = board[0].size();
        if (m == 0) return 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (isUpperLeftCorner(board, i, j)) {
                    ans++;
                }
            }
        }
        return ans;
    }

    bool isUpperLeftCorner(const vector<vector<char>> &board,
                           int row, int col) {
        if (board[row][col] != 'X') return false;
        return (row == 0 || board[row-1][col] == '.') &&
            (col == 0 || board[row][col-1] == '.');
    }
};

int main() {
    Solution solution;
    return 0;
}
