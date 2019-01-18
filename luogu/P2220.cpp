// https://www.luogu.org/problemnew/show/P2220
// [HAOI2012]容易题

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int N, M, K;

int qpow(int64_t x, int n) {
    int64_t ret = 1;
    while (n) {
        if (n&1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        n >>= 1;
    }
    return ret;
}

int sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    unordered_map<int, set<int>> rest;
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        rest[x].insert(y);
    }
    int s = ((1LL*(N+1)*N)/2) % MOD;
    int p = M - rest.size();
    int ret = qpow(s, p);
    for (const auto e: rest) {
        int t = s;
        for (int x: e.second) {
            t = sub(t, x);
        }
        ret = mul(ret, t);
    }
    printf("%d\n", ret);
    return 0;
}
