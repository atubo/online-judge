// https://leetcode.com/problems/sudoku-solver/
// 37. Sudoku Solver

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    void solveSudoku(vector<vector<char>> &board) {
        auto b = toInt(board);
        int empty = countEmpty(b);
        vector<int> row_masks(9), col_masks(9);
        for (int i = 0; i < 9; i++) {
            row_masks[i] = calcRowMask(b, i);
            col_masks[i] = calcColMask(b, i);
        }
        vector<vector<int>> block_masks(3, vector<int>(3));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                block_masks[i][j] = calcBlockMask(b, i, j);
            }
        }
        dfs(b, row_masks, col_masks, block_masks, empty);
        toChar(board, b);
    }

private:
    vector<vector<int>> toInt(const vector<vector<char>> &board) {
        vector<vector<int>> b(9, vector<int>(9));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                b[i][j] = (board[i][j] == '.' ? 0 : board[i][j]-'0');
            }
        }
        return b;
    }

    void toChar(vector<vector<char>>& board,
                const vector<vector<int>> &b) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = '0' + b[i][j];
            }
        }
    }

    int countEmpty(const vector<vector<int>> &board) {
        int ans = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!board[i][j]) ans++;
            }
        }
        return ans;
    }

    int calcRowMask(const vector<vector<int>> &board, int row) {
        int ans = 0;
        for (int i = 0; i < 9; i++) {
            int x = board[row][i];
            if (x > 0) ans |= 1 << x;
        }
        return ans;
    }

    int calcColMask(const vector<vector<int>> &board, int col) {
        int ans = 0;
        for (int i = 0; i < 9; i++) {
            int x = board[i][col];
            if (x > 0) ans |= 1 << x;
        }
        return ans;
    }

    int calcBlockMask(const vector<vector<int>> &board, int row, int col) {
        int ans = 0;
        for (int i = 3*row; i < 3*(row+1); i++) {
            for (int j = 3*col; j < 3*(col+1); j++) {
                int x = board[i][j];
                if (x > 0) ans |= 1 << x;
            }
        }
        return ans;
    }

    int calcBlank(const vector<vector<int>> &board,
                  const vector<int> &row_masks,
                  const vector<int> &col_masks,
                  const vector<vector<int>> &block_masks,
                  int x, int y) {
        int cnt = __builtin_popcount(row_masks[x]);
        cnt = max(cnt, __builtin_popcount(col_masks[y]));
        cnt = max(cnt, __builtin_popcount(block_masks[x/3][y/3]));
        return 9 - cnt;
    }


    void setState(int x, int y, int d,
                  vector<int> &row_masks,
                  vector<int> &col_masks,
                  vector<vector<int>> &block_masks) {
        row_masks[x] |= 1 << d;
        col_masks[y] |= 1 << d;
        block_masks[x/3][y/3] |= 1 << d;
    }

    void unsetState(int x, int y, int d,
                    vector<int> &row_masks,
                    vector<int> &col_masks,
                    vector<vector<int>> &block_masks) {
        unsigned int mask = ~(1U << d);
        row_masks[x] &= mask;
        col_masks[y] &= mask;
        block_masks[x/3][y/3] &= mask;
    }

    bool dfs(vector<vector<int>> &board,
             vector<int> &row_masks,
             vector<int> &col_masks,
             vector<vector<int>> &block_masks,
             int d) {
        if (d == 0) return true;
        int cx = -1, cy = -1;
        int maxpop = -1, candmask = -1;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] > 0) continue;
                int mask = row_masks[i] | col_masks[j] |
                    block_masks[i/3][j/3];
                int popcount = __builtin_popcount(mask);
                if (popcount > maxpop) {
                    maxpop = popcount;
                    candmask = mask;
                    cx = i;
                    cy = j;
                }
            }
        }

        for (int i = 1; i <= 9; i++) {
            if (!((candmask >> i) & 1)) {
                board[cx][cy] = i;
                setState(cx, cy, i, row_masks, col_masks, block_masks);
                if (dfs(board, row_masks, col_masks, block_masks, d-1)) {
                    return true;
                }
                unsetState(cx, cy, i, row_masks, col_masks, block_masks);
                board[cx][cy] = 0;
            }
        }
        return false;
    }
};

int main() {
    vector<vector<char>> board(9, vector<char>(9));
    for (int i = 0; i < 9; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 9; j++) {
            board[i][j] = s[j];
        }
    }
    Solution solution;
    solution.solveSudoku(board);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}
