// https://www.luogu.org/problemnew/show/P2160
// [SHOI2007]书柜的尺寸

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 72;
const int MAXT = 2110;
const int INF = 1e9;
int N;
int dp[MAXT][MAXT];
int S[MAXN];
struct Book {
    int h, t;
    bool operator > (const Book &other) const {
        if (h > other.h) return true;
        if (h < other.h) return false;
        return t > other.t;
    }
} books[MAXN];

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &books[i].h, &books[i].t);
    }
    sort(books+1, books+N+1, greater<Book>());
    for (int i = 1; i <= N; i++) {
        S[i] = S[i-1] + books[i].t;
    }
    for (int i = 0; i < MAXT; i++) {
        for (int j = 0; j < MAXT; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        int t = books[i+1].t;
        int h = books[i+1].h;
        for (int t1 = MAXT-1; t1 >= 0; t1--) {
            for (int t2 = MAXT-1; t2 >= 0; t2--) {
                int t3 = S[i] - t1 - t2;
                if (t3 < 0 || dp[t1][t2] == INF) continue;
                if (t1 == 0) dp[t1+t][t2] = min(dp[t1+t][t2],
                                                dp[t1][t2] + h);
                else dp[t1+t][t2] = min(dp[t1+t][t2], dp[t1][t2]);
                if (t2 == 0) dp[t1][t2+t] = min(dp[t1][t2+t],
                                                dp[t1][t2] + h);
                else dp[t1][t2+t] = min(dp[t1][t2+t], dp[t1][t2]);
                if (t3 == 0) dp[t1][t2] += h;
            }
        }
    }

    int ans = INT_MAX;
    for (int t1 = 1; t1 < MAXT; t1++) {
        for (int t2 = 1; t2 < MAXT; t2++) {
            int t3 = S[N] - t1 - t2;
            if (t3 <= 0 || dp[t1][t2] == INF) continue;
            ans = min(ans, max3(t1, t2, t3)*dp[t1][t2]);
        }
    }
    printf("%d\n", ans);

    return 0;
}
