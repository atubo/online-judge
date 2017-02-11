// https://www.luogu.org/problem/show?pid=1855
// 榨取kkksc03

#include <bits/stdc++.h>
using namespace std;

int dp[210][210];
int money[110], tt[110];

int N, M, T;

int main() {
    scanf("%d %d %d", &N, &M, &T);
    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &money[i], &tt[i]);
    }

    for (int i = 1; i <= N; i++) {
        for (int m = M; m >= money[i]; m--) {
            for (int t = T; t >= tt[i]; t--) {
                dp[m][t] = max(dp[m][t], dp[m-money[i]][t-tt[i]] + 1);
            }
        }
    }
    printf("%d\n", dp[M][T]);
    return 0;
}
