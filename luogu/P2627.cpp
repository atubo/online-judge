// https://www.luogu.org/problemnew/show/P2627
// 修剪草坪

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, K;
int64_t S[MAXN], dp[MAXN];

struct Item {
    int x;
    int64_t v;
} items[MAXN];
int front, back;

int main() {
    scanf("%d%d", &N, &K);
    K = min(N, K);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &S[i]);
        S[i] += S[i-1];
    }

    items[front++] = {0, -S[1]};
    for (int i = 1; i <= K; i++) {
        dp[i] = S[i];
        while (front > back && dp[i]-S[i+1] >= items[front-1].v) {
            front--;
        }
        items[front++] = {i, dp[i]-S[i+1]};
    }

    for (int i = K+1; i <= N; i++) {
        while (items[back].x < i-K-1) back++;
        dp[i] = items[back].v + S[i];
        while (front > back && dp[i]-S[i+1] >= items[front-1].v) {
            front--;
        }
        items[front++] = {i, dp[i]-S[i+1]};
    }
    printf("%lld\n", dp[N]);
    return 0;
}
