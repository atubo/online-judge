// https://www.luogu.org/problemnew/show/P2758
// 编辑距离

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;
int dp[MAXN][MAXN];

int min3(int a, int b, int c) {
    return min(a, min(b, c));
}

int main() {
    string A, B;
    cin >> A >> B;
    int N = A.length(), M = B.length();
    for (int i = 0; i <= N; i++) dp[i][0] = i;
    for (int i = 0; i <= M; i++) dp[0][i] = i;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min3(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
        }
    }
    printf("%d\n", dp[N][M]);
    return 0;
}
