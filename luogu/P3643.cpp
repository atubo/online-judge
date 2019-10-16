// https://www.luogu.org/problem/P3643
// [APIO2016]划艇

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 510;
int N;
struct Segment {
    int a, b;
} S[MAXN];
int dp1[MAXN][2*MAXN], dp2[MAXN][2*MAXN];
int INV[MAXN];

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int main() {
    scanf("%d", &N);

    INV[1] = 1;
    for (int i = 2; i <= N; i++) {
        INV[i] = mul(MOD-MOD/i, INV[MOD%i]);
    }

    vector<int> pts;
    pts.push_back(-1);
    for (int i = 1; i <= N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        S[i] = {a-1, b};
        pts.push_back(a-1);
        pts.push_back(b);
    }
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    int M = pts.size() - 1;
    for (int i = 1; i <= N; i++) {
        S[i].a = lower_bound(pts.begin(), pts.end(), S[i].a) - pts.begin();
        S[i].b = lower_bound(pts.begin(), pts.end(), S[i].b) - pts.begin() - 1;
    }

    dp1[0][0] = 1;
    for (int j = 0; j <= M; j++) dp2[0][j] = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = S[i].a; j <= S[i].b; j++) {
            int L = pts[j+1] - pts[j];
            int f = L;
            int x = L, y = 1;
            for (int k = i-1; k >= 0; k--) {
                (dp1[i][j] += mul(f, dp2[k][j-1])) %= MOD;
                if (S[k].a <= j && j <= S[k].b) {
                    f = mul(mul(f, ++x), INV[++y]);
                }
            }

        }
        for (int j = 1; j <= M; j++) {
            dp2[i][j] = (dp2[i][j-1] + dp1[i][j]) % MOD;
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            (ans += dp1[i][j]) %= MOD;
        }
    }

    printf("%d\n", ans);

    return 0;
}
