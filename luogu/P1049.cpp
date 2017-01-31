// https://www.luogu.org/problem/show?pid=1049
// 装箱问题

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 20010;
const int MAXN = 32;
int vol[MAXN];
bool dp[MAXV];

int main() {
    int V, N;
    scanf("%d", &V);
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &vol[i]);
    }

    dp[0] = true;

    for (int i = 1; i <= N; i++) {
        for (int v = V; v >= vol[i]; v--) {
            dp[v] |= dp[v-vol[i]];
        }
    }

    int vmax = V;
    for (; vmax >= 0; vmax--) {
        if (dp[vmax]) break;
    }

    printf("%d\n", V - vmax);
    return 0;
}
