// https://www.luogu.org/problemnew/show/P2167
// [SDOI2009]Bill的挑战

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000003;
int T, N, K;
int dp_prev[1<<15], dp_curr[1<<15];
int f1[1<<15], f2[1<<15], f3[1<<15];
int ALL, LEN;
char str[16][52];

int sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

void fmt1(int *f, int bits) {
    for (int i = 0; i < bits; i++) {
        for (int j = 0; j < (1<<bits); j++) {
            if (j>>i&1) {
                f[j] += f[j&(~(1U<<i))];
                if (f[j] >= MOD) f[j] -= MOD;
            }
        }
    }
}

void fmt2(int *f, int bits) {
    for (int i = 0; i < bits; i++) {
        for (int j = 0; j < (1<<bits); j++) {
            if (j>>i&1) {
                f[j] -= f[j&(~(1U<<i))];
                if (f[j] < 0) f[j] += MOD;
            }
        }
    }
}

void mobius(int *dp1, int *dp2) {
    for (int s = 0; s <= ALL; s++) {
        f1[s] = dp1[s^ALL];
        f2[s] = dp2[s^ALL];
    }
    fmt1(f1, N);
    fmt1(f2, N);
    for (int s = 0; s <= ALL; s++) {
        f3[s] = (1LL *f1[s] * f2[s]) % MOD;
    }
    fmt2(f3, N);

    for (int s = 0; s <= ALL; s++) {
        dp1[s] = f3[s^ALL];
    }
}


void getMasks(int pos, int mask, int &in, int &out) {
    in = out = 0;
    for (int i = 0; i < N; i++) {
        char c = str[i][pos];
        if ((mask>>i) & 1) {
            if (c == '?') in |= 1;
            else in |= 1<<(c-'a'+1);
        } else {
            if (c == '?') out |= 1;
            else out |= 1<<(c-'a'+1);
        }
    }
}

int getCount(int in, int out) {
    if (out&1) return 0;
    if (__builtin_popcount(in & (~1U)) > 1) return 0;
    if (__builtin_popcount(in & out) > 0) return 0;
    if ((in&(~1U)) == 0) return 26 - __builtin_popcount(out);
    else return 1;
}

void build(int pos, int *f) {
    for (int s = 1; s <= ALL; s++) {
        int in = 0, out = 0;
        for (int i = 0; i < N; i++) {
            char c = str[i][pos];
            if ((s>>i) & 1) {
                if (c == '?') in |= 1;
                else in |= 1<<(c-'a'+1);
            } else {
                if (c == '?') out |= 1;
                else out |= 1<<(c-'a'+1);
            }
        }
        int ret = 0;
        if (out&1) ret = 0;
        else if (__builtin_popcount(in & (~1U)) > 1) ret = 0;
        else if (__builtin_popcount(in & out) > 0) ret = 0;
        else if ((in&(~1U)) == 0) ret = 26 - __builtin_popcount(out);
        else ret = 1;
        f[s] = ret;
    }
}

int solve() {
    scanf("%d%d", &N, &K);
    ALL = (1<<N)-1;
    for (int i = 0; i < N; i++) {
        scanf("%s", str[i]);
    }
    LEN = strlen(str[0]);
    if (K > N || K < 0) return 0;
    memset(dp_prev, 0, sizeof(dp_prev));
    dp_prev[ALL] = 1;

    for (int i = 0; i < LEN; i++) {
        build(i, dp_curr);
        mobius(dp_prev, dp_curr);
    }

    if (K > 0) {
        int ans = 0;
        for (int s = 1; s <= ALL; s++) {
            if (__builtin_popcount(s) == K) (ans += dp_prev[s]) %= MOD;
        }
        return ans;
    } else {
        int ans = 1;
        for (int i = 0; i < LEN; i++) ans = mul(ans, 26);
        for (int s = 1; s <= ALL; s++) {
            ans = sub(ans, dp_prev[s]);
        }
        return ans;
    }
}


int main() {
    scanf("%d", &T);
    while (T--) {
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}
