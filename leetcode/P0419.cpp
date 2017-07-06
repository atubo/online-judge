// https://leetcode.com/problems/battleships-in-a-board/#/description
// 419. Battleships in a Board

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int M = board.size();
        if (M == 0) return 0;
        int N = board[0].size();
        if (N == 0) return 0;
        int ret = 0;
        for (int r = 0; r < M; r++) {
            for (int c = 0; c < N; c++) {
                ret += board[r][c] == 'X' &&
                    !(r > 0 && board[r-1][c] == 'X') &&
                    !(c > 0 && board[r][c-1] == 'X');
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
