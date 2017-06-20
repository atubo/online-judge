// https://www.luogu.org/problem/show?pid=1412
// 经营与开发

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int T[MAXN], A[MAXN];
double dp[MAXN];

int main() {
    int N, W;
    double K, C;
    scanf("%d%lf%lf%d", &N, &K, &C, &W);
    K /= 100; C /= 100;
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &T[i], &A[i]);
    }

    for (int i = N; i >= 1; i--) {
        if (T[i] == 1) dp[i] = max(A[i] - dp[i+1]*K, 0.0) + dp[i+1];
        else dp[i] = max(dp[i+1]*C - A[i], 0.0) + dp[i+1];
    }

    printf("%.2lf\n", W * dp[1]);
    return 0;
}
