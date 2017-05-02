// https://www.luogu.org/problem/show?pid=2889
// [USACO07NOV]挤奶的时间Milking Time

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;     // end, efficiency
int N, M, R;

int main() {
    scanf("%d%d%d", &N, &M, &R);
    vector<vector<PII>> milk(N);
    for (int i = 0; i < M; i++) {
        int s, e, p;
        scanf("%d%d%d", &s, &e, &p);
        milk[s].push_back(make_pair(e, p));
    }
    vector<int> dp(N+1);
    vector<int> mx(N+1);
    for (int i = N-1; i >= 0; i--) {
        dp[i] = dp[i+1];
        for (const auto &p: milk[i]) {
            int next = p.first + R;
            dp[i] = max(dp[i], p.second + (next > N ? 0 : mx[next]));
        }
        mx[i] = max(dp[i], mx[i+1]);
    }
    printf("%d\n", mx[0]);
    return 0;
}
