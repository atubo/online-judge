// https://www.luogu.org/problemnew/show/P3239
// [HNOI2015]亚瑟王

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 225, MAXR = 135;;
int T;
int N, R;
double P[MAXN];
int D[MAXN];
double dp[MAXR];

double prob(double p, int n) {
    double ans = 1 - pow(1-p, n);
    return ans;
}

void solve() {
    scanf("%d%d", &N, &R);
    for (int i = 1; i <= N; i++) {
        scanf("%lf%d", &P[i], &D[i]);
    }
    double ans = 0;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        double g = 0;
        for (int j = 0; j <= min(i-1, R); j++) {
            g += prob(P[i], R-j) * dp[j];
        }
        ans += g * D[i];
        for (int j = min(i, R); j >= 0; j--) {
            dp[j] = pow(1-P[i], R-j) * dp[j];
            if (j > 0) {
                dp[j] += prob(P[i], R-j+1) * dp[j-1];
            }
        }
    }
    printf("%.10lf\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
