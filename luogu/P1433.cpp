// https://www.luogu.org/problemnew/show/P1433
// 吃奶酪

#include <bits/stdc++.h>
using namespace std;

int N;
double X[20], Y[20];

double dp[2100000];

int key(int start, int mask) {
    return (start << 16) | mask;
}

double dist(int i, int j) {
    double dx = X[i] - X[j];
    double dy = Y[i] - Y[j];
    return sqrt(dx * dx + dy * dy);
}

double solve(int start, int mask) {
    if (mask == 0) return 0;

    int k = key(start, mask);
    if (dp[k] >= 0) return dp[k];

    double &ans = dp[k];
    ans = 1e60;
    for (int i = 1; i <= N; i++) {
        if ((mask >> i) & 1) {
            ans = min(ans, dist(start, i) + solve(i, mask & ~(1<<i)));
        }
    }
    return ans;
}

int main() {
    for (int i = 0; i < 2100000; i++) dp[i] = -1;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lf%lf", &X[i], &Y[i]);
    }
    double ans = solve(0, (1<<(N+1))-2);
    printf("%.2lf\n", ans);
    return 0;
}
