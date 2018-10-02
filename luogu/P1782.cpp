// https://www.luogu.org/problemnew/show/P1782
// 旅行商的背包

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010, MAXC = 10010;
int N, M, C;
int W[MAXN], V[MAXN], D[MAXN];
int buf[MAXC];
vector<int64_t> dp(MAXN), dp_next(MAXN);
int dpr[2][MAXC];

struct coeff {
    int a, b, c;
} co[5];

void solve0(int b, int c) {
    int64_t mx = dp[0];
    dp_next[0] = max(dp[0], dp[0] + c);
    for (int i = 1; i <= C; i++) {
        dp_next[i] = max(dp[i]+max(c, 0), mx + 1L*b*i + c);
        mx = max(mx, dp[i] - b*i);
    }
    swap(dp, dp_next);
}

int64_t F(int x, int a, int b) {
    return dp[x] + 1LL*a*x*x - 1LL*b*x;
}

void solve1(int a, int b, int c) {
    int p = 0, q = 0;
    buf[q++] = 0;
    dp_next[0] = max(dp[0], dp[0] + c);
    for (int i = 1; i <= C; i++) {
        while (q-p > 1 && F(buf[q-1], a, b) - F(buf[q-2], a, b) <= 
               2LL*a*i*(buf[q-1] - buf[q-2])) q--;
        int j = buf[q-1];
        dp_next[i] = max(dp[i]+max(0,c),
                         dp[j] + 1L*a*(i-j)*(i-j) + 1L*b*(i-j) + c);
        while (q-p > 1 &&
               (F(i, a, b) - F(buf[q-1], a, b)) * (buf[q-1] - buf[q-2]) >=
               (F(buf[q-1], a, b) - F(buf[q-2], a, b)) * (i - buf[q-1])) {
            q--;
        }
        buf[q++] = i;
    }
    swap(dp, dp_next);
}

void solve2(int a, int b, int c) {
    int p = 0, q = 0;
    buf[q++] = 0;
    dp_next[0] = max(dp[0], dp[0] + c);
    for (int i = 1; i <= C; i++) {
        while (q-p > 1 && F(buf[p+1], a, b) - F(buf[p], a, b) >=
               2LL*a*i*(buf[p+1] - buf[p])) p++;
        int j = buf[p];
        dp_next[i] = max(dp[i]+max(0, c),
                         dp[j] + 1L*a*(i-j)*(i-j) + 1L*b*(i-j) + c);
        while (q-p > 1 &&
               (F(i, a, b) - F(buf[q-1], a, b)) * (buf[q-1] - buf[q-2]) >=
               (F(buf[q-1], a, b) - F(buf[q-2], a, b)) * (i - buf[q-1])) {
            q--;
        }
        buf[q++] = i;
    }
    swap(dp, dp_next);
}

int main() {
    scanf("%d%d%d", &N, &M, &C);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &W[i], &V[i], &D[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d", &co[i].a, &co[i].b, &co[i].c);
    }
    for (int n = 0; n < N; n++) {
        int id1 = (n & 1), id0 = (id1 ^ 1);
        int *dp1 = dpr[id1], *dp0 = dpr[id0];
        int w = W[n], v = V[n], d = D[n];
        for (int r = 0; r < w; r++) {
            int p = 0, q = 0;
            buf[q++] = 0;
            for (int k = 0; k <= (C-r)/w; k++) {
                int i = r + k*w;
                if (q > p && (k - buf[p]) > d) p++;
                int j = r + buf[p]*w;
                dp1[i] = dp0[i];
                int t = dp0[j] + (k - buf[p]) * v;
                if (t > dp1[i]) dp1[i] = t;
                while (q > p && dp0[i]-k*v >= dp0[r+buf[q-1]*w]-buf[q-1]*v) q--;
                buf[q++] = k;
            }
        }
    }
    for (int i = 0; i <= C; i++) {
        dp[i] = dpr[(N-1)&1][i];
    }

    for (int m = 0; m < M; m++) {
        if (co[m].a == 0) solve0(co[m].b, co[m].c);
        else if (co[m].a > 0) solve1(co[m].a, co[m].b, co[m].c);
        else solve2(co[m].a, co[m].b, co[m].c);
    }

    printf("%ld", dp[C]);
    return 0;
}
