// https://www.luogu.org/problemnew/show/P2615
// 神奇的幻方

#include <bits/stdc++.h>
using namespace std;

int N;
int board[39][39];
int last_x, last_y;

void fill(int x, int y, int v) {
    board[x][y] = v;
    last_x = x;
    last_y = y;
}

void fill(int value) {
    if (last_x == 0 && last_y != N-1) fill(N-1, last_y+1, value);
    else if (last_y == N-1 && last_x != 0) fill(last_x-1, 0, value);
    else if (last_x == 0 && last_y == N-1) fill(last_x+1, last_y, value);
    else {
        if (board[last_x-1][last_y+1] == -1) fill(last_x-1, last_y+1, value);
        else fill(last_x+1, last_y, value);
    }
}

int main() {
    memset(board, -1, sizeof(board));
    scanf("%d", &N);
    board[0][N/2] = 1;
    last_x = 0, last_y = N/2;
    for (int i = 2; i <= N*N; i++) fill(i);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}
