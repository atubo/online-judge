// https://www.luogu.org/problemnew/show/P3558
// [POI2013]BAJ-Bytecomputer

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
const int INF = 1e9;
int N;
int A[MAXN], dp[MAXN][3];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = -1; i <= 1; i++) {
        dp[0][1+i] = INF;
    }
    dp[0][1+A[0]] = 0;
    for (int i = 1; i < N; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = INF;
        int x = A[i];
        // -1
        int t = dp[i-1][0];
        if (t < INF) {
            for (int j = 0; x-j >= -1; j++) {
                int y = x-j;
                dp[i][1+y] = min(dp[i][1+y], t + j);
            }
        }
        // 0
        t = dp[i-1][1];
        if (t < INF && x >= 0) dp[i][1+x] = min(dp[i][1+x], t);
        // 1
        t = dp[i-1][2];
        if (t < INF) {
            dp[i][2] = min(dp[i][2], t + 1 - x);
        }
    }
    int ans = min(dp[N-1][0], min(dp[N-1][1], dp[N-1][2]));
    if (ans < INF) printf("%d", ans);
    else printf("BRAK");

    return 0;
}
