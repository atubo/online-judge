// https://www.luogu.org/problemnew/show/P3257
// [JLOI2014]天天酷跑

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3F3F3F3F;
int N, M, C1, C2;
int A[MAXN][22];
int S[MAXN][22], NXT[MAXN][22];
int dp[MAXN][22][6];

void build() {
    for (int j = 1; j <= M; j++) {
        if (A[N][j] == -1) NXT[N][j] = N;
        else S[N][j] = A[N][j];
    }
    for (int i = N-1; i >= 0; i--) {
        for (int j = 1; j <= M; j++) {
            if (A[i][j] == -1) {
                NXT[i][j] = i;
                S[i][j] = 0;
            } else {
                NXT[i][j] = (j == M ? 0 : NXT[i+1][j+1]);
                S[i][j] = A[i][j] + (j == M ? 0 : S[i+1][j+1]);
            }
        }
    }
}

int jump(int i, int j, int c, int hmax) {
    int ret = -INF;
    if (c > 0 && (NXT[i][j] == 0 || NXT[i][j] > i + hmax) &&
        ((N-i <= M-j) || (j+hmax <= M))) {
        if (i+hmax > N) {
            ret = S[i][j];
        } else {
            ret = S[i][j]-S[i+hmax][j+hmax] + dp[i+hmax][j+hmax][c-1];
        }
    }
    return ret;
}


int solve(int hmax, int cmax) {
    for (int j = 1; j <= M; j++) {
        for (int c = 0; c < cmax; c++) {
            if (A[N][j] == -1) dp[N][j][c] = -INF;
            else dp[N][j][c] = A[N][j];
        }
    }

    for (int i = N-1; i >= 0; i--) {
        for (int j = 1; j <= M; j++) {
            if (A[i][j] == -1) {
                for (int c = 0; c < cmax; c++) dp[i][j][c] = -INF;
                continue;
            }
            for (int c = 0; c < cmax; c++){
                if (j == 1) {
                    dp[i][j][c] = A[i][j] + dp[i+1][j][cmax-1];
                    dp[i][j][c] = max(dp[i][j][c], jump(i, j, cmax, hmax));
                } else {
                    dp[i][j][c] = A[i][j] + dp[i+1][j-1][c];
                    dp[i][j][c] = max(dp[i][j][c], jump(i, j, c, hmax));
                }
            }
        }
    }

    return dp[0][1][cmax-1];
}

int main() {
    scanf("%d%d%d%d", &N, &M, &C1, &C2);
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &A[j][i]);
        }
    }
    build();

    int maxProfit = INT_MIN;
    int ansh = 1, ansc = 1;
    for (int cmax = 1; cmax <= 5; cmax++) {
        for (int hmax = 1; hmax*cmax < M; hmax++) {
            int profit = solve(hmax, cmax);
            if (profit >= 0) {
                int p = profit - C1*(hmax-1) - C2*(cmax-1);
                if (p > maxProfit) {
                    maxProfit = p;
                    ansh = hmax;
                    ansc = cmax;
                }
            }
        }
    }
    if (maxProfit == INT_MIN) {
        printf("mission failed\n");
    } else {
        printf("%d %d %d\n", maxProfit, ansc, ansh);
    }

    return 0;
}
