// https://www.luogu.org/problemnew/show/P1762
// 偶数

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000003;

int64_t qpow(int c) {
    int64_t ret = 1;
    for (int i = 1; i <= c; i++) {
        ret = (ret * 3) % MOD;
    }
    return ret;
}

int64_t solve(int64_t n) {
    if (n < 2) return n;
    int c = 63 - __builtin_clzll(n);
    int64_t ret = (qpow(c) + 2*solve(n - (1LL<<c))) % MOD;
    return ret;
}

int main() {
    int64_t n;
    scanf("%ld", &n);
    int64_t ans = ((n%MOD)*((n+1)%MOD)/2 + MOD - solve(n)) % MOD;
    printf("%ld\n", ans);
    return 0;
}
