// https://www.luogu.org/problemnew/show/P2396
// yyy loves Maths VII

#include <bits/stdc++.h>
using namespace std;

int N, M;
int dp[1<<24];
int ps[1<<24];
int A[24], B[2];
const int MOD = 1000000007;


int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        ps[1<<i] = A[i];
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &B[i]);
    }
    dp[0] = 1;
    for (int i = 1; i < (1 << N); i++) {
        int j = i & -i, k = i;
        ps[i] = ps[i ^ j] + ps[j];
        if (ps[i] == B[0] || ps[i] == B[1]) continue;
        while (k) {
            j = k & -k;
            dp[i] += dp[i ^ j];
            if (dp[i] >= MOD) dp[i] -= MOD;
            k ^= j;
        }
    }
    printf("%d\n", dp[(1<<N)-1]);
    return 0;
}
