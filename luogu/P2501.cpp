// https://www.luogu.org/problemnew/show/P2501
// [HAOI2006]数字序列

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35010;
int N;
int A[MAXN];
int dp[MAXN];
int len[MAXN];
int64_t dp2[MAXN];
int hi[MAXN], lo[MAXN];

int64_t cost(int s, int e) {
    if (e - s == 1) return 0;
    int64_t ans = 0;
    if (e == N+1) {
        for (int i = s+1; i <= N; i++) {
            ans += abs(A[i] - A[s]);
        }
        return ans;
    }
    if (s == 0) {
        for (int i = 1; i < e; i++) {
            ans += abs(A[i] - A[e]);
        }
        return ans;
    }

    hi[0] = lo[0] = 0;
    for (int i = s+1; i < e; i++) {
        if (A[i] > A[e]) {
            hi[i-s] = 1 + hi[i-s-1];
            lo[i-s] = lo[i-s-1];
        } else {
            hi[i-s] = hi[i-s-1];
            lo[i-s] = 1 + lo[i-s-1];
        }
    }
    int minflip = lo[e-s-1];
    int minpos = s;
    for (int i = s+1; i < e; i++) {
        int x = hi[i-s] + (lo[e-s-1] - lo[i-s]);
        if (x < minflip) {
            minpos = i;
            minflip = x;
        }
    }
    for (int i = s+1; i <= minpos; i++) {
        ans += abs(A[i] - A[s]);
    }
    for (int i = minpos+1; i < e; i++) {
        ans += abs(A[i] - A[e]);
    }
    return ans;
}


int main() {
    scanf("%d", &N);
    A[0] = INT_MIN;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i] = A[i] - i;
    }
    dp[0] = INT_MIN;
    for (int i = 1; i <= N; i++) {
        dp[i] = INT_MAX;
    }

    vector<vector<int>> pos(N+1);
    pos[0].push_back(0);

    for (int i = 1; i <= N; i++) {
        int p = upper_bound(dp, dp+N+1, A[i]) - dp;
        len[i] = p;
        dp[p] = A[i];
        pos[p].push_back(i);
    }

    int maxl = 0;
    for (int i = N; i > 0; i--) {
        if (dp[i] < INT_MAX) {
            maxl = i;
            break;
        }
    }
    printf("%d\n", N-maxl);

    int64_t ans = INT_MAX;
    for (int i = 1; i <= N; i++) {
        dp2[i] = INT_MAX;
        for (int j: pos[len[i]-1]) {
            if (j > i) break;
            if (A[j] <= A[i]) {
                dp2[i] = min(dp2[i], dp2[j] + cost(j, i));
            }
        }
        if (len[i] == maxl) {
            dp2[i] += cost(i, N+1);
            ans = min(ans, dp2[i]);
        }
    }
    printf("%ld\n", ans);

    return 0;
}
