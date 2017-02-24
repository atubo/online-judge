// https://www.luogu.org/problem/show?pid=2513
// [HAOI2009]逆序对数列

#include <bits/stdc++.h>
using namespace std;

const int MOD = 10000;

int dp[1010], ps[1010];

int add(int a, int b) {
    return (a + b) % MOD;
}

int sub(int a, int b) {
    return (a + MOD - b) % MOD;
}

int main() {
    int N, K;
    cin >> N >> K;
    dp[0] = 1;
    for (int k = 0; k <= K; k++) {
        ps[k] = 1;
    }
    for (int n = 1; n <= N; n++) {
        for (int k = K; k >= 0; k--) {
            int lo = max(0, k - (n - 1));
            dp[k] = sub(ps[k], (lo == 0 ? 0 : ps[lo-1]));
        }
        ps[0] = dp[0];
        for (int k = 1; k <= K; k++) {
            ps[k] = add(ps[k-1], dp[k]);
        }
    }
    cout << dp[K] << endl;
    return 0;
}
