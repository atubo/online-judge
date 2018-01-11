// https://www.luogu.org/problemnew/show/P2577
// [ZJOI2005]午餐

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
const int MAXT = 40000;
const int INF = 1e9;
int N;
struct Item {
    int a, b;
    bool operator > (const Item &other) const {
        if (b > other.b) return true;
        if (b < other.b) return false;
        return a > other.a;
    }
} items[MAXN];

int dp[201][40001];
int S[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &items[i].a, &items[i].b);
    }
    sort(items+1, items+N+1, greater<Item>());
    for (int i = 1; i <= N; i++) {
        S[i] = S[i-1] + items[i].a;
    }

    for (int j = 1; j <= MAXT; j++) dp[0][j] = INF;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= MAXT; j++) {
            if (j > S[i-1]) dp[i][j] = INF;
            else {
                dp[i][j] = max(S[i-1] - j + items[i].a + items[i].b,
                               dp[i-1][j]);
            }
            if (j >= items[i].a) {
                dp[i][j] = min(dp[i][j],
                               max(j + items[i].b, dp[i-1][j-items[i].a]));
            }
        }
    }
    int ans = INF;
    for (int j = 0; j <= MAXT; j++) {
        ans = min(ans, max(j, dp[N][j]));
    }
    printf("%d\n", ans);
    return 0;
}
