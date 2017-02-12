// https://www.luogu.org/problem/show?pid=1417
// 烹调方案

#include <bits/stdc++.h>
using namespace std;

struct Ingredient {
    int a, b, c;
    bool operator < (const Ingredient& other) const {
        return c * other.b < other.c * b;
    }
};

int N, T;
Ingredient A[55];

int main() {
    scanf("%d %d", &T, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].a);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].b);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].c);
    }
    sort(A, A+N);
    vector<int64_t> dp(T+1);
    for (int i = 1; i <= T; i++) {
        dp[i]= INT_MIN;
    }

    for (int i = 0; i < N; i++) {
        int64_t a = A[i].a, b = A[i].b, c = A[i].c;
        for (int t = T; t >= c; t--) {
            if (dp[t-c] != INT_MIN) {
                dp[t] = max(dp[t], dp[t-c] + (a-b*t));
            }
        }
    }

    int64_t ans = 0;
    for (int t = T; t >= 0; t--) {
        ans = max(ans, dp[t]);
    }
    printf("%lld\n", ans);
    return 0;
}
