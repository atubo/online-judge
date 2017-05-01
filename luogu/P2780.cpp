// https://www.luogu.org/problem/show?pid=2780
// [AHOI2016初中组]游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 75001;
using Mask = bitset<MAXM>;

vector<Mask> dp(260);
int N, K, A, B;
int L[MAXM], R[MAXM];

int main() {
    scanf("%d%d%d%d", &N, &K, &A, &B);
    int s = 0, x;

    dp[0].set(0);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &x);
        for (int k = min(i, K); k > 0; k--) {
            dp[k] |= (dp[k-1] << x);
        }
        s += x;
    }

    L[A] = INT_MIN/2;
    for (int i = A; i >= 0; i--) {
        if (dp[K][i]) {
            L[A] = i;
            break;
        }
    }
    for (int i = A+1; i <= B; i++) {
        L[i] = (dp[K][i] ? i : L[i-1]);
    }
    R[B] = INT_MAX/2;
    for (int i = B; i <= s; i++) {
        if (dp[K][i]) {
            R[B] = i;
            break;
        }
    }
    for (int i = B-1; i >= A; i--) {
        R[i] = (dp[K][i] ? i : R[i+1]);
    }

    int ret = 0;
    for (int i = A; i <= B; i++) {
        ret = max(ret, min(i-L[i], R[i]-i));
    }

    printf("%d\n", ret);
    return 0;
}
