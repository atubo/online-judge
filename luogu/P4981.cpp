// https://www.luogu.org/problem/P4981
// 父子

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000009;

int qpow(int64_t x, int n) {
    int64_t ret = 1;
    while (n) {
        if (n & 1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        n >>= 1;
    }
    return ret;
}

int T, N;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        printf("%d\n", qpow(N, N-1));
    }
    return 0;
}
