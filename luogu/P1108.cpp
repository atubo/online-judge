// https://www.luogu.org/problem/show?pid=1108
// 低价购买

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;

const int MAXN = 5010;
PII A[MAXN];
int B[MAXN];
int N;
PII dp[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].first);
        A[i].second = i;
    }
    sort(A, A+N);
    B[A[0].second] = 0;
    for (int i = 1; i < N; i++) {
        if (A[i].first == A[i-1].first) {
            B[A[i].second] = B[A[i-1].second];
        } else {
            B[A[i].second] = B[A[i-1].second]+1;
        }
    }
    int maxb = B[A[N-1].second];
    for (int i = 0; i < N; i++) {
        B[i] = maxb - B[i];
    }

    for (int i = 0; i < N; i++) {
        dp[i] = make_pair(-1, 0);
    }

    for (int i = 0; i < N; i++) {
        int x = B[i];
        int maxLen = 0;
        int total = 1;
        for (int j = 0; j < x; j++) {
            if (dp[j].first > maxLen) {
                maxLen = dp[j].first;
                total = 0;
            }
            if (dp[j].first == maxLen) {
                total += dp[j].second;
            }
        }
        dp[x] = make_pair(maxLen+1, total);
    }

    int maxLen = -1;
    for (int i = 0; i <= maxb; i++) {
        maxLen = max(maxLen, dp[i].first);
    }

    int ways = 0;
    for (int i = 0; i <= maxb; i++) {
        if (dp[i].first == maxLen) {
            ways += dp[i].second;
        }
    }

    printf("%d %d\n", maxLen, ways);

    return 0;
}
