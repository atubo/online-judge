// https://www.luogu.org/problemnew/show/P3220
// [HNOI2012]与非

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1024;
int64_t N, K, L, R;
int64_t A[MAXN];
vector<int> BACK(64, -1);
int64_t dp[64];

bool correlate(int p, int q) {
    int64_t mask = (1UL << (K-1-p)) | (1UL << (K-1-q));
    for (int i = 0; i < N; i++) {
        int64_t x = A[i] & mask;
        int pcnt = __builtin_popcountll(x);
        if (pcnt == 1) return false;
    }
    return true;
}

int64_t solve(int64_t x, int64_t curr, int pos, bool bounded) {
    if (pos == K) return 1;
    int64_t xd = (x >> (K-pos-1)) & 1;
    if (BACK[pos] != -1) {
        int64_t d = (curr >> BACK[pos]) & 1;
        int64_t nc = (d == 1 ? curr|(1UL<<pos) : curr);
        if (!bounded) return solve(x, nc, pos+1, false);
        if (xd > d) {
            return solve(x, nc, pos+1, false);
        }
        if (xd < d) return 0;
        return solve(x, nc, pos+1, true);
    } else {
        if (bounded) {
            if (xd == 0) return solve(x, curr, pos+1, true);
            return solve(x, curr, pos+1, false) +
                solve(x, curr|(1UL<<pos), pos+1, true);
        } else {
            if (dp[pos] > -1) return dp[pos];
            return dp[pos] = solve(x, curr, pos+1, false) +
                solve(x, curr|(1UL<<pos), pos+1, false);
        }
    }
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%ld%ld%ld%ld", &N, &K, &L, &R);
    for (int i = 0; i < N; i++) {
        scanf("%ld", &A[i]);
    }
    for (int i = 0; i < K; i++) {
        for (int j = i+1; j < K; j++) {
            if (correlate(i, j)) BACK[j] = i;
        }
    }
    int64_t ans = solve(min(R, (1L<<K)-1), 0, 0, true);
    memset(dp, -1, sizeof(dp));
    if (L > 0) ans -= solve(min(L-1, (1L<<K)-1), 0, 0, true);
    printf("%ld\n", ans);
    return 0;
}
