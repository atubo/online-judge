// https://www.luogu.org/problemnew/show/P4071
// [SDOI2016]排列计数

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 1000010;
int inv[MAXN], fac[MAXN], facinv[MAXN], ps[MAXN];

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

void init() {
    inv[0] = inv[1] = 1;
    facinv[0] = facinv[1] = 1;
    fac[0] = fac[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        inv[i] = 1ll * (MOD-MOD/i) * inv[MOD%i] % MOD;
        facinv[i] = mul(facinv[i-1], inv[i]);
        fac[i] = mul(fac[i-1], i);
    }
    ps[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        if (i&1) {
            ps[i] = sub(ps[i-1], facinv[i]);
        } else {
            ps[i] = add(ps[i-1], facinv[i]);
        }
    }
}

int T;
int N, M;

int main() {
    init();
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        int64_t ret = mul(mul(fac[N], facinv[M]), ps[N-M]);
        printf("%ld\n", ret);
    }
    return 0;
}
