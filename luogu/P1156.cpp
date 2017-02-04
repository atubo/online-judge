// https://www.luogu.org/problem/show?pid=1156
// 垃圾陷阱

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

const int MAXT = 1010;
const int MAXD = 110;
int dp[MAXD];
int D, G;
const int MINF = -1e9;

int main() {
    scanf("%d %d", &D, &G);
    vector<PII> trash(MAXT);
    int maxt = 0;
    for (int i = 0; i < G; i++) {
        int t, f, h;
        scanf("%d %d %d", &t, &f, &h);
        trash[t].first += f;
        trash[t].second += h;
        maxt = max(maxt, t);
    }

    dp[0] = 10;
    for (int i = 1; i <= D; i++) {
        dp[i] = MINF;
    }

    int ans = -1;
    int last = 0;
    for (int t = 1; t <= maxt; t++) {
        int f = trash[t].first;
        int h = trash[t].second;
        bool survived = false;
        for (int d = D; d >= 0; d--) {
            dp[d]--;
            if (dp[d] < 0) dp[d] = MINF;
            else dp[d] += f;
            if (d >= h && dp[d-h] > 0) {
                dp[d] = max(dp[d], dp[d-h]-1);
            }
            if (dp[d] >= 0) survived = true;
        }
        if (dp[D] >= 0) {
            ans = t;
            break;
        }
        if (survived) {
            last = t;
        } else {
            break;
        }
    }

    if (last == maxt) last += dp[0];

    if (ans >= 0) {
        printf("%d\n", ans);
    } else {
        printf("%d\n", last);
    }
    return 0;
}
