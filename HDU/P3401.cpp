// http://acm.hdu.edu.cn/showproblem.php?pid=3401
// Trade

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;
const int64_t MINF = -1e9;

int dp[MAXN][MAXN];

int f(int e, int j, int a) {
    return dp[e][j] + j * a;
}

int main() {
    dp[0][0] = 0;
    for (int i = 1; i < MAXN; i++) {
        dp[0][i] = MINF;
    }

    int t;
    scanf("%d", &t);
    while (t--) {
        int T, maxp, W;
        scanf("%d %d %d", &T, &maxp, &W);
        for (int d = 1; d <= T; d++) {
            int A, B, C, D;
            scanf("%d %d %d %d", &A, &B, &C, &D);
            int e = max(0, d-W-1);

            deque<int> q;
            for (int j = 0; j <= maxp; j++) {
                dp[d][j] = dp[d-1][j];
                while (q.size() > 0 && f(e, q.back(), A) <= f(e, j, A)) {
                    q.pop_back();
                }
                q.push_back(j);
                while (j - q.front() > C) {
                    q.pop_front();
                }
                dp[d][j] = max(dp[d][j], f(e, q.front(), A) - j*A);
            }

            q.clear();
            for (int j = maxp; j >= 0; j--) {
                while (q.size() > 0 && f(e, q.back(), B) <= f(e, j, B)) {
                    q.pop_back();
                }
                q.push_back(j);
                while (q.front() - j > D) {
                    q.pop_front();
                }
                dp[d][j] = max(dp[d][j], f(e, q.front(), B) - j*B);
            }
        }
        printf("%d\n", dp[T][0]);
    }

    return 0;
}
