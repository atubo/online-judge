// https://www.luogu.org/problemnew/show/P2890
// [USACO07OPEN]便宜的回文Cheapest Palindrome

#include <bits/stdc++.h>
using namespace std;

int N, M;
int chg[26];
int T[2010];
int dp[2010][2010];

int solve(int L, int R) {
    if (L > R) return 0;
    if (dp[L][R] >= 0) return dp[L][R];
    int &ans = dp[L][R];
    if (L == R) return ans = 0;
    if (T[L] == T[R]) {
        ans = solve(L+1, R-1);
    } else {
        ans = min(chg[T[R]] + solve(L, R-1),
                  chg[T[L]] + solve(L+1, R));
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    char s[2010];
    scanf("%s", s);
    for (int i = 0; i < M; i++) {
        T[i] = s[i] - 'a';
    }
    for (int i = 0; i < N; i++) {
        int c1, c2;
        scanf("%s %d %d", s, &c1, &c2);
        chg[s[0]-'a'] = min(c1, c2);
    }

    memset(dp, -1, sizeof(dp));
    int ret = solve(0, M-1);
    printf("%d\n", ret);
    return 0;
}
