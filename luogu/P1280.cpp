// https://www.luogu.org/problem/show?pid=1280
// 尼克的任务

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    vector<vector<int> >  tasks(N+1);
    for (int i = 0; i < K; i++) {
        int p, t;
        scanf("%d %d", &p, &t);
        tasks[p].push_back(t);
    }
    vector<int> dp(N+2);
    dp[N+1] = 0;
    for (int i = N; i >= 1; i--) {
        if (tasks[i].empty()) {
            dp[i] = dp[i+1];
        } else {
            dp[i] = INT_MAX;
            for (int j = 0; j < (int)tasks[i].size(); j++) {
                int t = tasks[i][j];
                dp[i] = min(dp[i], t + dp[i+t]);
            }
        }
    }
    printf("%d\n", N - dp[1]);
    return 0;
}
