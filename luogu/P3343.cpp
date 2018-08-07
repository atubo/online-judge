// https://www.luogu.org/problemnew/show/P3343
// [ZJOI2015]地震后的幻想乡

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 50;
struct Edge {
    int u, v;
} edges[MAXM];

int num_edges[1024][1024];
double dp[MAXM][1024];

int N, M;

double solve(int k, int mask) {
    if (dp[k][mask] != 0) return dp[k][mask];
    double &ret = dp[k][mask];
    for (int m = mask; m;) {
        m = (m-1) & mask;
        if ((m & 1) == 0) continue;
        int kpt = k + num_edges[m][mask&(~m)];
        ret += 1.0 / (1 + kpt) - solve(kpt, m);
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M;  i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        edges[i] = {a, b};
    }
    for (int m1 = 1; m1 < 1024; m1++) {
        for (int m2 = m1; m2;) {
            m2 = (m2-1) & m1;
            int m3 = m1 & (~m2);
            for (int i = 0; i < M; i++) {
                int u = edges[i].u;
                int v = edges[i].v;
                if ((((m2>>u)&1) && (m3>>v)&1) ||
                    (((m2>>v)&1) && (m3>>u)&1)) {
                    num_edges[m2][m3]++;
                }
            }
        }
    }
    double ans = solve(0, (1<<N)-1);
    printf("%.6lf\n", ans);
    return 0;
}
