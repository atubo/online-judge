// https://www.luogu.org/problemnew/show/P1463
// [POI2002][HAOI2007]反素数

#include <bits/stdc++.h>
using namespace std;

const int MAXG = 2100;
int P[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
int dp[9][MAXG+1];
int A[MAXG+1];

int pow(int x, int n) {
    int64_t ret = 1;
    for (int i = 1; i <= n; i++) {
        ret *= x;
        if (ret > INT_MAX) return INT_MAX;
    }
    return ret;
}

int solve(int k, int pos) {
    if (dp[pos][k] >= 0) return dp[pos][k];
    int &ret = dp[pos][k] = pow(P[pos], k-1);
    if (pos == 8) {
        return ret;
    }
    for (int f = 2; f*f <= k; f++) {
        if (k % f) continue;
        int64_t ans = min(1LL * INT_MAX,
                          1LL * pow(P[pos], f-1) * solve(k/f, pos+1));
        ret = min(ret, (int)ans);
        ans = min(1LL * INT_MAX,
                  1LL * pow(P[pos], k/f-1) * solve(f, pos+1));
        ret = min(ret, (int)ans);
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < 9; i++) dp[i][1] = 1;
    for (int i = 1; i <= MAXG; i++) {
        solve(i, 0);
    }

    A[MAXG] = dp[0][MAXG];
    for (int g = MAXG-1; g >= 1; g--) {
        A[g] = min(A[g+1], dp[0][g]);
    }
    sort(A, A + MAXG + 1);
    auto end = unique(A, A + MAXG + 1);

    int n;
    scanf("%d", &n);
    auto it = upper_bound(A, end, n);
    printf("%d\n", *(--it));

    return 0;
}
