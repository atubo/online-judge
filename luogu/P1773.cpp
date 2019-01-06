// https://www.luogu.org/problemnew/show/P1773
// 符文之语_NOI导刊2010提高（02）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int M;
int R[MAXN][MAXN];
int dp[MAXN][52];
int T[52][52];
string S;

int main() {
    cin >> S;
    cin >> M;
    const int N = S.length();
    for (int i = 0; i < N; i++) {
        R[i][i] = (S[i]-'0') % M;
        for (int j = i+1; j < N; j++) {
            R[i][j] = (R[i][j-1]*10 + S[j]-'0') % M;
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            T[i][j] = (i*j) % M;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < M; k++) dp[i][k] = 100;
        dp[i][R[0][i]] = 0;
    }
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < M; k++) {
            if (dp[i][k] == 100) continue;
            for (int j = i+1; j < N; j++) {
                int x = T[k][R[i+1][j]];
                dp[j][x] = min(dp[j][x], dp[i][k]+1);
            }
        }
    }

    int r1, k1, r2, k2;
    for (int r = 0; r < M; r++) {
        if (dp[N-1][r] < 100) {
            r1 = r;
            k1 = dp[N-1][r];
            break;
        }
    }
    for (int r = M-1; r >= 0; r--) {
        if (dp[N-1][r] < 100) {
            r2 = r;
            k2 = dp[N-1][r];
            break;
        }
    }
    printf("%d %d %d %d", r1, k1, r2, k2);

    return 0;
}
