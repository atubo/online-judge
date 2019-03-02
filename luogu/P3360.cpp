// https://www.luogu.org/problemnew/show/P3360
// 偷天换日

#include <bits/stdc++.h>
using namespace std;

int64_t dp[310][610];
int N;
int idx;

void process(int id, int x, int t) {
    memset(dp[id], 0xFF, (N+1)*sizeof(int64_t));
    if (2*t > N) {
        dp[id][0] = 0;
        return;
    }
    dp[id][2*t] = 0;
    for (int i = 0; i < x; i++) {
        int w, c;
        scanf("%d%d", &w, &c);
        for (int j = N; j >= c; j--) {
            if (dp[id][j-c] >= 0) {
                dp[id][j] = max(dp[id][j], dp[id][j-c] + w);
            }
        }
    }
    dp[id][0] = 0;
}

void merge(int id, int id1, int id2, int t) {
    memset(dp[id], 0xFF, (N+1)*sizeof(int64_t));
    if (2*t > N) {
        dp[id][0] = 0;
        return;
    }
    for (int i = 0; i <= N-2*t; i++) {
        for (int j = 0; j <= i; j++) {
            int k = i - j;
            if (dp[id1][j] >= 0 && dp[id2][k] >= 0) {
                dp[id][i+2*t] = max(dp[id][i+2*t], dp[id1][j] + dp[id2][k]);
            }
        }
    }
    dp[id][0] = 0;
}

int dfs() {
    int curr = idx++;
    int t, x;
    scanf("%d%d", &t, &x);
    if (x > 0) {
        process(curr, x, t);
    } else {
        int id1 = dfs();
        int id2 = dfs();
        merge(curr, id1, id2, t);
    }
    return curr;
}

int main() {
    scanf("%d", &N);
    N--;
    dfs();
    int64_t ans = 0;
    for (int i = 0; i <= N; i++) {
        ans = max(ans, dp[0][i]);
    }
    printf("%ld", ans);
    return 0;
}
