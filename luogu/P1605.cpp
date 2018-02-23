// https://www.luogu.org/problemnew/show/P1605
// 迷宫

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};
int maze[6][6];
bool vis[6][6];
int N, M, T, SX, SY, FX, FY;
int result;

bool passable(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M && !maze[x][y];
}

void dfs(int x, int y) {
    if (x == FX && y == FY) {
        result++;
        return;
    }
    vis[x][y] = true;
    for (int d = 0; d < 4; d++) {
        int nx = x + DX[d];
        int ny = y + DY[d];
        if (passable(nx, ny) && !vis[nx][ny]) {
            dfs(nx,ny);
        }
    }
    vis[x][y] = false;
}

int main() {
    scanf("%d%d%d", &N, &M, &T);
    scanf("%d%d%d%d", &SX, &SY, &FX, &FY);
    SX--; SY--; FX--; FY--;
    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        maze[x-1][y-1] = 1;
    }

    dfs(SX, SY);
    printf("%d\n", result);
    return 0;
}
