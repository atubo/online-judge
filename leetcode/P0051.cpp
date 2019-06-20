// https://leetcode.com/problems/n-queens/
// 51. N-Queens

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ret;
        vector<int> board(n);
        vector<int> vert(n), diag0(2*n-1), diag1(2*n-1);
        for (int i = 0; i < n; i++) {
            dfs(board, vert, diag0, diag1, 0, i, ret);
        }
        return ret;
    }

private:
    void dfs(vector<int> &board,
             vector<int> &vert,
             vector<int> &diag0,
             vector<int> &diag1,
             int row, int col,
             vector<vector<string>> &ret) {
        int n = board.size();
        board[row] = col;
        if (row == n-1) {
            ret.push_back(convert(board));
            return;
        }

        vert[col] = 1;
        diag0[row+col] = 1;
        diag1[row-col+n-1] = 1;

        for (int i = 0; i < n; i++) {
            if (vert[i] == 0 && diag0[row+1+i] == 0 && diag1[row-i+n] == 0) {
                dfs(board, vert, diag0, diag1, row+1, i, ret);
            }
        }

        vert[col] = 0;
        diag0[row+col] = 0;
        diag1[row-col+n-1] = 0;
    }

    vector<string> convert(const vector<int> &board) {
        const int n = board.size();
        vector<string> ret;
        for (int i = 0; i < n; i++) {
            string line(n, '.');
            line[board[i]] = 'Q';
            ret.push_back(line);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
