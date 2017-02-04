// https://www.luogu.org/problem/show?pid=1156
// 垃圾陷阱

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

const int MAXT = 1010;
int dp[130];
int D, G;
const int MINF = -1e9;

int main() {
    scanf("%d %d", &D, &G);
    vector<vector<PII> > trash(MAXT);
    int maxt = 0;
    for (int i = 0; i < G; i++) {
        int t, f, h;
        scanf("%d %d %d", &t, &f, &h);
        trash[t].push_back(make_pair(f, h));
        maxt = max(maxt, t);
    }

    int MAXD = D + 25;

    dp[0] = 10;
    for (int i = 1; i <= MAXD; i++) {
        dp[i] = MINF;
    }

    int ans = -1;
    int last = 0;
    for (int t = 1; t <= maxt; t++) {
        for (int d = MAXD; d >= 0; d--) {
            dp[d]--;
            if (dp[d] < 0) dp[d] = MINF;
        }

        for (int g = 0; g < (int)trash[t].size(); g++) {
            int f = trash[t][g].first;
            int h = trash[t][g].second;

            for (int d = MAXD; d >= 0; d--) {
                if (dp[d] >= 0) dp[d] += f;
                if (d >= h && dp[d-h] >= 0) {
                    dp[d] = max(dp[d], dp[d-h]);
                }
            }
        }

        for (int d = MAXD; d >= D; d--) {
            if (dp[d] >= 0) {
                ans = t;
                goto OUT;
            }
        }

        if (dp[0] >= 0) last = t;
        else break;
    }

OUT:

    if (last == maxt) last += dp[0];

    if (ans >= 0) {
        printf("%d\n", ans);
    } else {
        printf("%d\n", last);
    }
    return 0;
}
