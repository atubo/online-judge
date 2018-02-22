// https://www.luogu.org/problemnew/show/P2476
// [SCOI2008]着色方案

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int encode(int x, int c[5]) {
    int ret = (x << 20);
    for (int i = 0; i < 5; i++) {
        ret |= (c[i] << i*4);
    }
    return ret;
}

void decode(int code, int &x, int c[5]) {
    x = code >> 20;
    for (int i = 0; i < 5; i++) {
        c[i] = (code >> i*4) & 0xF;
    }
}

int transform(int x, int c[5], int p) {
    int cn[5];
    for (int i = 0; i < 5; i++) cn[i] = c[i];
    if (x > 0) cn[x-1]++;
    cn[p]--;
    x = p;
    return encode(x, cn);
}

int dp[1<<23];

int solve(int code) {
    if (dp[code] >= 0) return dp[code];
    int &ret = dp[code];
    if (code == 0) return ret = 1;
    int x, c[5] = {0};
    decode(code, x, c);

    ret = 0;
    for (int p = 4; p >= 0; p--) {
        if (c[p] == 0) continue;
        ret = add(ret, mul(c[p], solve(transform(x, c, p))));
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    int K;
    scanf("%d", &K);
    int c[5] = {0};
    for (int i = 0; i < K; i++) {
        int x;
        scanf("%d", &x);
        c[x-1]++;
    }
    printf("%d\n", solve(encode(0, c)));
    return 0;
}
