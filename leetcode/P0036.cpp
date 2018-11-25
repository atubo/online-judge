#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            if (!checkRow(board, i)) return false;
        }
        for (int i = 0; i < 9; i++) {
            if (!checkCol(board, i)) return false;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!checkBox(board, i, j)) return false;
            }
        }
        return true;
    }

private:
    bool checkRow(const vector<vector<char>>& board, int r) {
        vector<int> cnt(9);
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == '.') continue;
            int x = board[r][c] - '1';
            if (x < 0 || x > 8) return false;
            cnt[x]++;
        }
        for (int i = 0; i < 9; i++) {
            if (cnt[i] > 1) return false;
        }
        return true;
    }

    bool checkCol(const vector<vector<char>>& board, int c) {
        vector<int> cnt(9);
        for (int r = 0; r < 9; r++) {
            if (board[r][c] == '.') continue;
            int x = board[r][c] - '1';
            if (x < 0 || x > 8) return false;
            cnt[x]++;
        }
        for (int i = 0; i < 9; i++) {
            if (cnt[i] > 1) return false;
        }
        return true;
    }

    bool checkBox(const vector<vector<char>>& board,
                  int rb, int cb) {
        vector<int> cnt(9);
        for (int r = rb*3; r < rb*3+3; r++) {
            for (int c = cb*3; c < cb*3+3; c++) {
                if (board[r][c] == '.') continue;
                int x = board[r][c] - '1';
                if (x < 0 || x > 8) return false;
                cnt[x]++;
            }
        }
        for (int i = 0; i < 9; i++) {
            if (cnt[i] > 1) return false;
        }
        return true;
    }
};

int main() {
    Solution solution;
    return 0;
}
