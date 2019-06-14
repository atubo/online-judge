// https://www.luogu.org/problemnew/show/P1398
// [NOI2013]书法家

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 152, MAXM = 512;
int f4, f8, INF, ans;
int f1[MAXN][MAXN], f2[MAXN][MAXN], f3[MAXN][MAXN];
int f5[MAXN][MAXN], f6[MAXN][MAXN], f7[MAXN][MAXN];
int f9[MAXN][MAXN], f10[MAXN][MAXN], f11[MAXN][MAXN];
int s1[MAXN][MAXN], s2[MAXN][MAXN];
int s[MAXN];

int N, M;
int A[MAXM][MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &A[j][N-i+1]);
        }
    }
    memset(s1, -63, sizeof(s1));
    memset(s2, -63, sizeof(s2));

    memset(f1, -63, sizeof(f1));
    memset(f2, -63, sizeof(f2));
    memset(f3, -63, sizeof(f3));
    memset(f5, -63, sizeof(f5));
    memset(f6, -63, sizeof(f6));
    memset(f7, -63, sizeof(f7));
    memset(f9, -63, sizeof(f9));
    memset(f10, -63, sizeof(f10));
    memset(f11, -63, sizeof(f11));

    INF = -f1[0][0];
    f4 = f8 = ans = -INF;

    for (int j = 1; j <= M; j++) {
        for (int i = 1; i <= N; i++) s[i] = s[i-1] + A[j][i];
        for (int l = 1; l <= N; l++) {
            for (int r = l+2; r <= N; r++) {
                f11[l][r] = max(f11[l][r], f10[l][r])+A[j][l]+A[j][r];
                ans = max(ans, f11[l][r]);
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l+2; r <= N; r++) {
                f10[l][r] = max(f10[l][r], f9[l][r]) + s[r] - s[l-1];
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l+2; r <= N; r++) {
                f9[l][r] = max(f9[l][r], f8) + A[j][l] + A[j][r];
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l+2; r <= N; r++) {
                f8 = max(f8, f7[l][r]);
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l+2; r <= N; r++) {
                f7[l][r] = f6[l][r] + s[r] - s[l-1];
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l+2; r <= N; r++) {
                f6[l][r] = max(f6[l][r], f5[l][r]) + A[j][l] + A[j][r];
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l+2; r <= N; r++) {
                f5[l][r] = f4 + s[r] - s[l-1];
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l+1; r <= N; r++) {
                f4 = max(f4, f3[l][r]);
            }
        }

        for (int l = 1; l <= N; l++) {
            int tmp = -INF;
            for (int r = l+1; r <= N; r++) {
                tmp = max(tmp, f2[l][r-1]);
                f3[l][r] = max(f3[l][r], tmp) + s[r] - s[l-1];
            }
        }

        for (int r = 1; r <= N; r++) {
            int tmp = s2[r+1][r];
            for (int l = r; l; l--) {
                tmp = max(tmp, s2[l][r]);
                f2[l][r] = max(s1[l-1][r], tmp) + s[r] - s[l-1];
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = l; r <= N; r++) {
                f1[l][r] = max(0, f1[l][r]) + s[r] - s[l-1];
            }
        }

        for (int l = 1; l <= N; l++) {
            for (int r = N; r; r--) {
                s2[l][r] = max(f2[l][r], s2[l][r+1]);
            }
        }

        for (int r = 1; r <= N; r++) {
            for (int l = 1; l <= N; l++) {
                s1[l][r] = max(f1[l][r], s1[l-1][r]);
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}
