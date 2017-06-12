// https://www.luogu.org/problem/show?pid=1799
// 数列_NOI导刊2010提高（06）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int A[MAXN], dp[MAXN];
int N;

int solve() {
    dp[0] = 0;
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        dp[i] = INT_MIN;
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && i - j >= A[i] - A[j]) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
        ret = max(ret, dp[i]);
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    printf("%d\n", solve());
    return 0;
}
