// https://www.luogu.org/problem/show?pid=1472
// 奶牛家谱 Cow Pedigrees

#include <bits/stdc++.h>
using namespace std;

const int MOD = 9901;
int add(int a, int b) {
    return (a + b) % MOD;
}

int sub(int a, int b) {
    return (a + MOD - b) % MOD;
}

int mul(int a, int b) {
    return (a * b) % MOD;
}

int dp[110][210];
int N, K;

int main() {
    cin >> N >> K;
    dp[0][0] = 1;
    for (int k = 1; k <= K; k++) {
        dp[k][0] = dp[k][1] = 1;
        for (int n = 2; n <= N; n++) {
            for (int m = 1; m < n-1; m++) {
                dp[k][n] = add(dp[k][n], mul(dp[k-1][m], dp[k-1][n-m-1]));
            }
        }
    }

    cout << sub(dp[K][N], dp[K-1][N]) << endl;
    return 0;
}
