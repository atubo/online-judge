// https://www.luogu.org/problemnew/show/P3622
// [APIO2007]动物园

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
int N, C;
int dp[MAXN][32];

struct Kid {
    int e;
    int fear, like;
} kids[50010];

bool check(const Kid &kid, int mask) {
    return (kid.fear & mask) > 0 ||
        (kid.like & ~mask) > 0;
}

int countKids(const vector<Kid> &kids, int mask) {
    int cnt = 0;
    for (const auto &k: kids) {
        if (check(k, mask)) cnt++;
    }
    return cnt;
}

int solve(const vector<vector<Kid>> &kidsByPos) {
    int ans = 0;
    for (int m0 = 0; m0 < 32; m0++) {
        memset(dp, -1, sizeof(dp));
        dp[0][m0] = countKids(kidsByPos[0], m0);
        int idx = 0;
        for (int i = 0; i < N-5; i++) {
            while (idx < C && kids[idx].e < i+1) idx++;
            for (int m = 0; m < 16; m++) {
                if (dp[i][m] < 0 && dp[i][m|16] < 0) continue;
                for (int d = 0; d < 2; d++) {
                    int nm = ((m << 1) & 31) | d;
                    int cnt = 0;
                    int idx1 = idx;
                    while (idx1 < C && kids[idx1].e == i+1) {
                        cnt += (kids[idx1].fear & nm) ||
                            (kids[idx1].like & ~nm);
                        idx1++;
                    }
                    if (dp[i][m] >= 0) {
                        dp[i+1][nm] = max(dp[i+1][nm], dp[i][m] + cnt);
                    }
                    if (dp[i][m|16] >= 0) {
                        dp[i+1][nm] = max(dp[i+1][nm], dp[i][m|16] + cnt);
                    }
                }
            }
        }
        for (int m1 = 0; m1 < 32; m1++) {
            if (dp[N-5][m1] < 0) continue;
            for (int i = 1; i <= 4; i++) {
                int nm = ((m1<<i) & 31) | ((m0>>(5-i)) & 0xFF);
                int pm = ((m1<<(i-1)) & 31) | ((m0>>(6-i)) & 0xFF);
                dp[N-5+i][nm] = max(
                    dp[N-5+i][nm],
                    dp[N-6+i][pm] + countKids(kidsByPos[N-5+i], nm)
                    );
            }
        }
        for (int m = 0; m < 32; m++) {
            ans = max(ans, dp[N-1][m]);
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &C);
    vector<vector<Kid>> kidsByPos(N);
    for (int i = 0; i < C; i++) {
        int e, f, l;
        scanf("%d%d%d", &e, &f, &l);
        e--;
        Kid kid{e, 0, 0};
        for (int j = 0; j < f; j++) {
            int x;
            scanf("%d", &x);
            x--;
            int mask = 1 << (x >= e ? 4-(x-e) : 4-(x-e+N));
            kid.fear |= mask;
        }
        for (int j = 0; j < l; j++) {
            int x;
            scanf("%d", &x);
            x--;
            int mask = 1 << (x >= e ? 4-(x-e) : 4-(x-e+N));
            kid.like |= mask;
        }
        kids[i] = kid;
        kidsByPos[e].push_back(kid);
    }

    int ans = (N >= 5 ? solve(kidsByPos): 0);
    printf("%d\n", ans);
    return 0;
}
