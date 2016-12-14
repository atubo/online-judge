// http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1201
// 整数划分
#include <bits/stdc++.h>
using namespace std;

int64_t MOD = 1000000007;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int dp[50001][320];

int main() {
    int N;
    cin >> N;
    dp[0][0] = 1;
    for (int n = 1; n <= N; n++) {
        for (int i = 1; i <= (int)sqrt(2*n); i++) {
            if (n < i) break;
            dp[n][i] = add(dp[n-i][i], dp[n-i][i-1]);
        }
    }
    int ans = 0;
    for (int i = 1; i < 320; i++) {
        ans = add(ans, dp[N][i]);
    }
    cout << ans << endl;
    return 0;
}
