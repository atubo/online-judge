// https://www.luogu.org/problemnew/show/P4430
// 小猴打架

#include <bits/stdc++.h>
using namespace std;

const int MOD = 9999991;
int N;

int64_t qpow(int64_t x, int n) {
    int64_t ret = 1;
    while (n) {
        if (n & 1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        n >>= 1;
    }
    return ret;
}

int solve() {
    if (N <= 2) return 1;
    int64_t ans = qpow(N, N-3);
    for (int i = 1; i <= N; i++) {
        ans = (ans * i) % MOD;
    }
    return ans;
}

int main() {
    scanf("%d", &N);

    printf("%d\n", solve());
    return 0;
}
