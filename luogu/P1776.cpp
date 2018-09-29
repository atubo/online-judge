// https://www.luogu.org/problemnew/show/P1776
// 宝物筛选_NOI导刊2010提高（02）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000;
const int MAXW = 40010;
int N, C;
int V[MAXN], W[MAXN];
int64_t dp[MAXW];
int idx;

void split(int val, int wt, int cnt) {
    int mask = 1;
    while (cnt >= mask) {
        V[idx] = mask * val;
        W[idx] = mask * wt;
        idx++;
        cnt -= mask;
        mask <<= 1;
    }
    if (cnt > 0) {
        V[idx] = cnt * val;
        W[idx] = cnt * wt;
        idx++;
    }
}

void solve(int cap) {
    const int n = idx;
    for (int i = 0; i < n; i++) {
        for (int j = C; j >= W[i]; j--) {
            dp[j] = max(dp[j], V[i]+dp[j-W[i]]);
        }
    }
    printf("%ld", dp[cap]);
}

int main() {
    scanf("%d%d", &N, &C);
    for (int i = 0; i < N; i++) {
        int val, wt, cnt;
        scanf("%d%d%d", &val, &wt, &cnt);
        split(val, wt, cnt);
    }

    solve(C);
    
    return 0;
}
