// https://www.luogu.org/problemnew/show/P1436
// 棋盘分割

#include <bits/stdc++.h>
using namespace std;

int dp[1<<16];
int B[8][8];

int encode(int k, int x1, int y1, int x2, int y2) {
    return (k << 12) | (x1 << 9) | (y1 << 6) | ((x2-1) << 3) | (y2-1);
}

bool isFeasible(int k, int x1, int y1, int x2, int y2) {
    return k <= (x2 - x1 - 1) + (y2 - y1 - 1) + 1;
}

int eval(int x1, int y1, int x2, int y2) {
    int ret = 0;
    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
            ret += B[x][y];
        }
    }
    return ret;
}

int solve(int k, int x1, int y1, int x2, int y2) {
    int code = encode(k, x1, y1, x2, y2);
    if (dp[code] >= 0) return dp[code];
    int &ret = dp[code] = INT_MAX;
    if (k == 1) {
        int tmp = eval(x1, y1, x2, y2);
        ret = tmp * tmp;
        return ret;
    }
    for (int x = x1 + 1; x < x2; x++) {
        if (isFeasible(k-1, x, y1, x2, y2)) {
            int tmp = eval(x1, y1, x, y2);
            int next = solve(k-1, x, y1, x2, y2);
            ret = min(ret, tmp * tmp + next);
        }
        if (isFeasible(k-1, x1, y1, x, y2)) {
            int tmp = eval(x, y1, x2, y2);
            int next = solve(k-1, x1, y1, x, y2);
            ret = min(ret, tmp * tmp + next);
        }
    }
    for (int y = y1 + 1; y < y2; y++) {
        if (isFeasible(k-1, x1, y, x2, y2)) {
            int tmp = eval(x1, y1, x2, y);
            int next = solve(k-1, x1, y, x2, y2);
            ret = min(ret, tmp * tmp + next);
        }
        if (isFeasible(k-1, x1, y1, x2, y)) {
            int tmp = eval(x1, y, x2, y2);
            int next = solve(k-1, x1, y1, x2, y);
            ret = min(ret, tmp * tmp + next);
        }
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    printf("%d", solve(n, 0, 0, 8, 8));
    return 0;
}
