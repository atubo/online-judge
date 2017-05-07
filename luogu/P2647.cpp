// https://www.luogu.org/problem/show?pid=2647
// 最大收益

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int MAXN = 3010;
int dp[MAXN];
PII item[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &item[i].second, &item[i].first);
    }
    sort(item+1, item+N+1, greater<PII>());
    for (int i = 1; i <= N; i++) {
        for (int j = i; j >= 1; j--) {
            dp[j] = max(dp[j], dp[j-1] + item[i].second - item[i].first * (j-1));
        }
    }
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        ret = max(ret, dp[i]);
    }
    printf("%d\n", ret);
    return 0;
}
