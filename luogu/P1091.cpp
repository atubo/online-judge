// https://www.luogu.org/problem/show?pid=1091
// 合唱队形

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int f[MAXN], g[MAXN], A[MAXN];
int len[2][MAXN], len2[MAXN];
int N;

void dp(int d) {
    memset(f, 0x7F, sizeof(f));
    f[0] = INT_MIN;
    for (int i = 1; i <= N; i++) {
        int p = lower_bound(f, f+MAXN, A[i]) - f;
        len[d][i] = p;
        f[p] = min(f[p], A[i]);
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    dp(0);
    reverse(A+1, A+N+1);
    dp(1);
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        ans = max(ans, len[0][i] + len[1][N+1-i]);
    }
    printf("%d\n", N-ans+1);
    return 0;
}
