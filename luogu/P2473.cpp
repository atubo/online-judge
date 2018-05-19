// https://www.luogu.org/problemnew/show/P2473
// [SCOI2008]奖励关

#include <bits/stdc++.h>
using namespace std;

int K, N;
int S[16], prereq[16];
double dp[110][65536];

int main() {
    scanf("%d%d", &K, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
        int x;
        while (scanf("%d", &x) && x != 0) {
            prereq[i] |= (1 << (x-1));
        }
    }

    for (int k = K-1; k >= 0; k--) {
        for (int mask = 0; mask < (1<<N); mask++) {
            for (int x = 0; x < N; x++) {
                double r = dp[k+1][mask];
                if ((mask | prereq[x]) == mask) {
                    r = max(r, S[x] + dp[k+1][mask|(1<<x)]);
                }
                dp[k][mask] += r;
            }
            dp[k][mask] /= N;
        }
    }

    printf("%.6f\n", dp[0][0]);

    return 0;
}
