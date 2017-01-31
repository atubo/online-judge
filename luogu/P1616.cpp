// https://www.luogu.org/problem/show?pid=1616
// 疯狂的采药

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 10010;
const int MAXT = 100010;
int dp[MAXT];
int wt[MAXM], value[MAXM];


int main() {
    int T, M;
    scanf("%d %d", &T, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &wt[i], &value[i]);
    }

    for (int m = 1; m <= M; m++) {
        for (int t = wt[m]; t <= T; t++) {
            dp[t] = max(dp[t], dp[t-wt[m]] + value[m]);
        }
    }
    printf("%d\n", dp[T]);
    return 0;
}
