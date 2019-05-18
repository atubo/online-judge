// https://www.luogu.org/problemnew/show/P3281
// [SCOI2013]数数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MOD = 20130427;
int B;
int N, M;
int L[MAXN], R[MAXN];
int64_t BI[MAXN];   // 1, B, B^2, ...
int64_t SB1[MAXN];  // 1, 1+B, 1+B+B^2, ...
int64_t SB2[MAXN];
int64_t AP1[MAXN], AP2[MAXN];

void build() {
    BI[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        BI[i] = (B * BI[i-1]) % MOD;
    }
    SB1[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        SB1[i] = (SB1[i-1] + BI[i]) % MOD;
    }
    SB2[0] = -1;
    SB2[1] = 0;
    for (int i = 2; i < MAXN; i++) {
        SB2[i] = (B * SB1[i-2]) % MOD;
    }
}

void build2(const int *a, int n) {
    AP1[n] = 0;
    AP1[n-1] = a[n-1] - 1;
    for (int i = n-2; i >= 0; i--) {
        AP1[i] = (AP1[i+1]*B + a[i]) % MOD;
    }

    AP2[0] = a[0];
    for (int i = 1; i < n; i++) {
        AP2[i] = (a[i]*BI[i] + AP2[i-1]) % MOD;
    }
}

void rmlz(int *a, int &n) {
    int cnt = 0;
    for (int i = n-1; i >= 0; i--) {
        if (a[i] > 0) break;
        cnt++;
    }
    n -= cnt;
}

void sub1(int *a, int &n) {
    for (int i = 0; i < n; i++) {
        if (a[i] >= 1) {
            a[i]--;
            break;
        }
        a[i] = B-1;
    }
    rmlz(a, n);
}

int64_t solve(const int *a, int n) {
    int64_t ans = 0;
    int64_t tb = ((1LL*B*(B-1))/2) % MOD;
    for (int i = 0; i < n-1; i++) {
        int64_t c = (BI[i]*SB1[i]) % MOD;
        int64_t t1 = ((n-i-1)*BI[n-i-2]) % MOD;
        int64_t t2 = (1 + SB2[n-i-2]) % MOD;
        int64_t t = (t1 + MOD - t2) % MOD;
        t = (t*c) % MOD;
        t = (t*tb) % MOD;

        (ans += t) %= MOD;
    }

    build2(a, n);

    for (int i = 0; i < n; i++) {
        int64_t c = (BI[i]*SB1[i]) % MOD;
        // [1, Ai-1]
        int64_t ta = (1LL*a[i]*(a[i]-1)/2) % MOD;
        int64_t t = (((AP1[i+1]+1)*c%MOD)*(n-i)) % MOD;
        t = (t * ta) % MOD;
        (ans += t) %= MOD;

        // [Ai+1, B-1]
        ta = (1LL*B*(B-1)/2 - 1LL*a[i]*(a[i]+1)/2) % MOD;
        t = ((AP1[i+1]*c%MOD)*(n-i)) % MOD;
        t = (t * ta) % MOD;
        (ans += t) %= MOD;

        // Ai
        t = ((AP1[i+1]*c%MOD)*(n-i)) % MOD;
        int64_t f = 1 + (i > 0 ? AP2[i-1] : 0);
        t = (t + (f*(n-i)%MOD)*SB1[i]) % MOD;
        t = (t * a[i]) % MOD;
        (ans += t) %= MOD;
    }
    return ans;
}

int main() {
    scanf("%d", &B);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &L[N-1-i]);
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &R[M-1-i]);
    }

    build();
    rmlz(L, N);
    rmlz(R, M);

    int64_t ans = solve(R, M);
    if (N > 0) {
        sub1(L, N);
        ans = (ans + MOD - solve(L, N)) % MOD;
    }
    printf("%ld\n", ans);
    return 0;
}
