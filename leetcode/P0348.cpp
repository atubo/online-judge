// https://leetcode.com/problems/design-tic-tac-toe/
// Design Tic-Tac-Toe

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class TicTacToe {
public:
    TicTacToe(int n): n_(n) {
        alloc(n);
    }

    ~TicTacToe() {
        dealloc();
    }

    int move(int row, int col, int player) {
        player--;
        if (++horz_[player][row] == n_) return player+1;
        if (++vert_[player][col] == n_) return player+1;
        if (row == col) {
            if (++diag0_[player] == n_) return player+1;
        }
        if (row + col == n_-1) {
            if (++diag1_[player] == n_) return player+1;
        }
        return 0;
    }

private:
    int n_;
    int *horz_[2], *vert_[2];
    int diag0_[2], diag1_[2];

    void alloc(int n) {
        for (int i = 0; i < 2; i++) {
            horz_[i] = new int[n]{};
            vert_[i] = new int[n]{};
        }
        diag0_[0] = diag0_[1] = 0;
        diag1_[0] = diag1_[1] = 0;
    }

    void dealloc() {
        for (int i = 0; i < 2; i++) {
            delete[] horz_[i];
            delete[] vert_[i];
        }
    }
};

int main() {
    return 0;
}
