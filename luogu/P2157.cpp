// https://www.luogu.org/problemnew/show/P2157
// [SDOI2009]学校食堂

#include <bits/stdc++.h>
using namespace std;

const int inf = INT_MAX/4;
const int MAXN = 1010;
int dp[MAXN][256][16];
int C, N;
int T[MAXN], B[MAXN];

#define f(i,j,k) dp[i][j][k+8]

int cost(int i, int j) {
    if (!i) return 0;
    return T[i] ^ T[j];
}

int main() {
    scanf("%d", &C);
    while (C--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            scanf("%d%d", &T[i], &B[i]);
        }
        for (int i = 1; i <= N+1; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = -8; k < 8; k++) {
                    f(i, j, k) = inf;
                }
            }
        }

        f(1, 0, -1) = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = -8; k < 8; k++) {
                    if (f(i, j, k) == inf) continue;
                    if (j & 1) {
                        f(i+1, j>>1, k-1) = min(f(i+1, j>>1, k-1),
                                                f(i, j, k));
                    } else {
                        for (int l = 0; l <= B[i]; l++) {
                            if ((j>>l) & 1) continue;
                            bool ok = true;
                            for (int q = 0; q < l; q++) {
                                if ((((j>>q) & 1) == 0) && (l - q) > B[i+q]) {
                                    ok = false;
                                    break;
                                }
                            }
                            if (ok) {
                                f(i, j|(1<<l), l) =
                                    min(f(i, j|(1<<l), l),
                                        f(i, j, k) + cost(i+k, i+l));
                            }
                        }
                    }
                }
            }
        }

        int ans = inf;
        for (int k = -8; k < 0; k++) {
            ans = min(ans, f(N+1, 0, k));
        }
        printf("%d\n", ans);
    }
    return 0;
}
