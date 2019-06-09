// https://www.luogu.org/problemnew/show/P1731
// [NOI1999]生日蛋糕

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7F7F7F7F;
int N, M;
int B[16], C[16];
int ans = INF;

int solve1(int rmax, int hmax, int v) {
    if (v <= 0) return INF;
    for (int r = rmax; r >= 1; r--) {
        if (v % (r*r) != 0) continue;
        int h = v / (r*r);
        if (h <= hmax) return 2*r*h;
        break;
    }
    return INF;
}


int dfs(int rmax, int hmax, int d, int v, int s0) {
    if (d == 0) return v == 0 ? 0 : INF;
    if (d == 1) return solve1(rmax, hmax, v);
    if (v < B[d]) return INF;
    if (s0 + C[d] > ans) return INF;
    if (2*v/rmax + s0 > ans) return INF;    // this cut is critical
    int ret = INF;
    for (int r = rmax; r >= d; r--) {
        for (int h = d; h <= hmax; h++) {
            if (r*r*h > v-B[d-1]) break;
            int vr = v - r*r*h;
            int s = 2*r*h;
            ret = min(ret, s + dfs(r-1, h-1, d-1, vr, s+s0));
        }
    }
    return ret;
}


int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        B[i] = B[i-1] + i*i*i;
        C[i] = C[i-1] + 2*i*i;
    }
    for (int r = 28; r >= M; r--) {
        int s0 = r*r;
        for (int h = M; r*r*h <= N-B[M-1]; h++) {
            int vr = N - r*r*h;
            ans = min(ans, s0 + 2*r*h + dfs(r-1, h-1, M-1, vr, s0+2*r*h));
        }
    }
    ans = (ans == INF ? 0 : ans);
    printf("%d\n", ans);
    return 0;
}
