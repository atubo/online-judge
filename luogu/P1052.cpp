// https://www.luogu.org/problem/show?pid=1052
// 过河

#include <bits/stdc++.h>
using namespace std;

int L, S, T, M;
int dp[10100];
int A[110], B[110];

void solve1() {
    int ans = 0;
    for (int i = 1; i <= M; i++) {
        ans += (A[i] % T == 0);
    }
    printf("%d\n", ans);
}

void calc(int x) {
    if (x < S) return;
    for (int i = max(0, x-T); i <= x-S; i++) {
        dp[x] = min(dp[x], dp[i]);
    }
    if (binary_search(A, A+M+1, x)) dp[x]++;
}

void solve2() {
    sort(A, A+M+1);
    int dmax = T * T + 1;
    for (int i = 1; i <= M; i++) {
        B[i] = B[i-1] + max(0, A[i] - A[i-1] - dmax);
    }
    for (int i = 1; i <= M; i++) {
        A[i] -= B[i];
    }
    L -= B[M];
    L = min(A[M] + dmax, L);
    memset(dp, 0x7f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= L+S-1; i++) {
        calc(i);
    }
    int ans = INT_MAX;
    for (int i = L; i <= L+S-1; i++) {
        ans = min(ans, dp[i]);
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &L);
    scanf("%d %d %d", &S, &T, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d", &A[i]);
    }
    if (S == T) solve1();
    else solve2();
    return 0;
}
