// https://www.luogu.org/problemnew/show/P1233
// 木棍加工

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
int N;
int dp[MAXN];

struct Stick {
    int l, w;
    bool operator < (const Stick &other) const {
        if (l < other.l) return true;
        if (l > other.l) return false;
        return w < other.w;
    }
} S[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &S[i].l, &S[i].w);
    }
    sort(S, S+N);

    int ans = 0;
    for (int i = 0; i < N; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (S[i].w < S[j].w) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
        ans = max(ans, dp[i]);
    }
    printf("%d", ans);

    return 0;
}
