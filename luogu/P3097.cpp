// https://www.luogu.org/problem/P3097
// [USACO13DEC]最优挤奶Optimal Milking

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40010;
int N, D;
int M[MAXN];
int BLK;
int dp[210][4];
int dp2[210];
int dp3[210][2];

void build(int idx) {
    int iend = (idx == N/BLK ? (N % BLK) + 1 : BLK);
    if (iend == 1) {
        dp[idx][0] = 0;
        dp[idx][1] = 0;
        dp[idx][2] = M[idx*BLK];
        dp[idx][3] = M[idx*BLK];
        return;
    }
    // left end is 0
    dp2[0] = 0;
    dp2[1] = M[idx*BLK+1];
    for (int i = 2; i < iend; i++) {
        dp2[i] = max(dp2[i-1], M[idx*BLK+i] + dp2[i-2]);
    }
    dp[idx][0] = dp2[iend-2];
    dp[idx][1] = dp2[iend-1];

    // left end is 1
    dp2[0] = M[idx*BLK];
    dp2[1] = max(M[idx*BLK], M[idx*BLK+1]);
    for (int i = 2; i < iend; i++) {
        dp2[i] = max(dp2[i-1], M[idx*BLK+i] + dp2[i-2]);
    }
    dp[idx][2] = dp2[iend-2];
    dp[idx][3] = dp2[iend-1];
}

int solve() {
    dp3[0][0] = max(dp[0][0], dp[0][2]);
    dp3[0][1] = max(dp[0][1], dp[0][3]);
    for (int i = 1; i <= N/BLK; i++) {
        dp3[i][0] = max(dp3[i-1][0] + max(dp[i][2], dp[i][0]),
                        dp3[i-1][1] + dp[i][0]);
        dp3[i][1] = max(dp3[i-1][0] + max(dp[i][3], dp[i][1]),
                        dp3[i-1][1] + dp[i][1]);
    }
    return max(dp3[N/BLK][0], dp3[N/BLK][1]);
}


int main() {
    scanf("%d%d", &N, &D);
    for (int i = 0; i < N; i++) {
        scanf("%d", &M[i]);
    }
    BLK = max(3, int(sqrt(N)));
    for (int i = 0; i <= N/BLK; i++) {
        build(i);
    }
    int64_t ans = 0;
    for (int i = 0; i < D; i++) {
        int p, m;
        scanf("%d%d", &p, &m);
        p--;
        M[p] = m;
        build(p/BLK);
        ans += solve();
    }
    printf("%ld\n", ans);

    return 0;
}
