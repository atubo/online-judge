// https://leetcode.com/problems/word-search/
// 79. Word Search

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
    bool exist(vector<vector<char>>& board, string word) {
        if (word.empty()) return true;
        const int n = board.size();
        if (n == 0) return false;
        const int m = board[0].size();
        if (m == 0) return false;
        vector<vector<bool>> vis(n, vector<bool>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == word[0]) {
                    if (dfs(board, word, vis, i, j, 0)) return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(const vector<vector<char>> &board,
             const string &word,
             vector<vector<bool>> &vis,
             int x, int y, int pos) {
        const int n = board.size();
        const int m = board[0].size();
        if (pos == (int)word.length()-1) return true;
        vis[x][y] = true;
        for (int d = 0; d < 4; d++) {
            int x2 = x + DX[d];
            int y2 = y + DY[d];
            if (inRange(x2, y2, n, m) && !vis[x2][y2] &&
                board[x2][y2] == word[pos+1]) {
                if (dfs(board, word, vis, x2, y2, pos+1)) return true;
            }
        }
        vis[x][y] = false;
        return false;
    }

    bool inRange(int x, int y, int n, int m) {
        return 0 <= x && x < n && 0 <= y && y < m;
    }
};

int main() {
    Solution solution;
    return 0;
}
