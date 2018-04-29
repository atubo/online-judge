// https://www.luogu.org/problemnew/show/P2507
// [SCOI2008]配对

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;
int A[MAXN], B[MAXN];

struct Pair {
    int a, b;
} P[MAXN];

int64_t dp[MAXN];
int64_t INF = 2e11;

int64_t cost(const Pair &p) {
    int d = p.a - p.b;
    return (d == 0 ? INF : abs(d));
}

int64_t exchange(int i) {
    Pair t1 = P[i-1];
    Pair t2 = P[i];
    swap(t1.b, t2.b);
    return cost(t1) + cost(t2);
}

int64_t exchange2(int i) {
    Pair t1 = P[i-2];
    Pair t2 = P[i-1];
    Pair t3 = P[i];
    int tmp = t3.b;
    t3.b = t1.b;
    t1.b = t2.b;
    t2.b = tmp;
    int64_t ans = cost(t1) + cost(t2) + cost(t3);
    t1 = P[i-2];
    t2 = P[i-1];
    t3 = P[i];
    tmp = t1.b;
    t1.b = t3.b;
    t3.b = t2.b;
    t2.b = tmp;
    ans = min(ans, cost(t1) + cost(t2) + cost(t3));
    return ans;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &A[i], &B[i]);
    }
    sort(A+1, A+N+1);
    sort(B+1, B+N+1);
    for (int i = 1; i <= N; i++) {
        P[i] = {A[i], B[i]};
    }

    dp[0] = 0;
    dp[1] = cost(P[1]);
    for (int i = 2; i <= N; i++) {
        dp[i] = min(dp[i-2] + exchange(i),
                    dp[i-1] + cost(P[i]));
        if (i >= 3) {
            dp[i] = min(dp[i], dp[i-3] + exchange2(i));
        }
        dp[i] = min(dp[i], INF);
    }

    printf("%lld\n", (dp[N] == INF ? -1 : dp[N]));

    return 0;
}
