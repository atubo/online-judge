// https://www.luogu.org/problem/show?pid=1489
// 猫狗大战

#include <bits/stdc++.h>
using namespace std;

bool dp[101][8001];
int N;
int A[201];

int main() {
    scanf("%d", &N);
    int s = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        s += A[i];
    }

    dp[0][0] = true;
    for (int i = 1; i <= N; i++) {
        for (int m = s/2; m >= 0; m--) {
            for (int k = 0; k <= (N+1)/2; k++) {
                if (k > 0 && m >= A[i]) dp[k][m] |= dp[k-1][m-A[i]];
            }
        }
    }

    int x = 0;
    for (int m = 0; m <= s/2; m++) {
        if (dp[N/2][m]) x = m;
        if ((N & 1) && dp[(N+1)/2][m]) x = m;
    }

    printf("%d %d\n", x, s - x);
    return 0;
}
