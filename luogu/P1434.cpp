// https://www.luogu.org/problemnew/show/P1434
// 滑雪

#include <bits/stdc++.h>
using namespace std;

int R, C;
int H[110][110], dp[110][110];

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

int solve(int r, int c) {
    if (dp[r][c] >= 0) return dp[r][c];
    int &ret = dp[r][c];
    int prev = 0;
    for (int d = 0; d < 4; d++) {
        int rn = r + DX[d];
        int cn = c + DY[d];
        if (inRange(rn, cn) && H[rn][cn] > H[r][c]) {
            prev = max(prev, solve(rn, cn));
        }
    }
    return ret = prev + 1;
}

int main() {
    scanf("%d%d", &R, &C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &H[i][j]);
        }
    }
    memset(dp, -1, sizeof(dp));
    int ret = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++) {
            ret = max(ret, solve(i, j));
        }
    }
    printf("%d\n", ret);
    return 0;
}
