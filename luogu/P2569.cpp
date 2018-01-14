// https://www.luogu.org/problemnew/show/P2569
//[SCOI2010]股票交易

#include <bits/stdc++.h>
using namespace std;

const int64_t INF = 1e10;
const int MAXN = 2010;
int64_t dp[MAXN][MAXN];
int W, T, MAXP;
int AP[MAXN], BP[MAXN], AS[MAXN], BS[MAXN];
struct Item {
    int x;
    int64_t p;
} items[MAXN];
int front, back;

int main() {
    scanf("%d%d%d", &T, &MAXP, &W);
    for (int i = 1; i <= T; i++) {
        scanf("%d%d%d%d", &AP[i], &BP[i], &AS[i], &BS[i]);
    }

    for (int i = 1; i <= MAXP; i++) {
        dp[0][i] = -INF;
    }

    for (int i = 1; i <= W+1; i++) {
        for (int j = 0; j <= AS[i]; j++) {
            dp[i][j] = max(dp[i-1][j], - int64_t(j) * AP[i]);
        }
        for (int j = AS[i]+1; j <= MAXP; j++) {
            dp[i][j] = max(dp[i-1][j], -INF);
        }
    }

    for (int i = W+2; i <= T; i++) {
        int prev = i - W - 1;
        front = back = 0;
        for (int j = 0; j <= MAXP; j++) {
            dp[i][j] = dp[i-1][j];
            while (front > back && dp[prev][j] + j * AP[i] >= items[front-1].p) {
                front--;
            }
            items[front++] = {j, dp[prev][j] + j * AP[i]};
            while (items[back].x < j - AS[i]) back++;
            dp[i][j] = max(dp[i][j], items[back].p - j * AP[i]);
        }

        front = back = 0;
        for (int j = MAXP; j >= 0; j--) {
            while (front > back && dp[prev][j] + j * BP[i] >= items[front-1].p) {
                front--;
            }
            items[front++] = {j, dp[prev][j] + j * BP[i]};
            while (items[back].x > j + BS[i]) back++;
            dp[i][j] = max(dp[i][j], items[back].p - j * BP[i]);
        }
    }

    printf("%lld\n", dp[T][0]);

    return 0;
}
