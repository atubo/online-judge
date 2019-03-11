// https://www.luogu.org/problemnew/show/P1803
// 凌乱的yyy / 线段覆盖

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
struct Match {
    int a, b;
    bool operator < (const Match &other) const {
        if (b != other.b) return b < other.b;
        return a < other.a;
    }
} M[MAXN];

int dp[MAXN];
int last[MAXN];

int N;

int main() {
    memset(last, -1, sizeof(last));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        M[i] = {a, b};
    }
    sort(M, M+N);
    int tmax = 0;
    for (int i = 0; i < N; i++) {
        int a = M[i].a, b = M[i].b;
        last[b] = max(last[b], a);
        tmax = max(tmax, b);
    }
    for (int i = 1; i <= tmax; i++) {
        dp[i] = dp[i-1];
        if (last[i] >= 0) {
            dp[i] = max(dp[i], dp[last[i]]+1);
        }
    }
    printf("%d\n", dp[tmax]);

    return 0;
}
