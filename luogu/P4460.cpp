// https://www.luogu.org/problemnew/show/P4460
// [CQOI2018]解锁屏幕

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000007;
const int MAXN = 19;
int N;
int dp[1<<MAXN][MAXN];
int middle[MAXN][MAXN];

struct Point {
    int x, y;
} pts[MAXN];

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

bool online(Point p1, Point p2, const Point &p3) {
    if (p1.x == p2.x) {
        if (p1.y > p2.y) swap(p1, p2);
        return p3.x == p1.x && p1.y <= p3.y && p3.y <= p2.y;
    }
    if (p1.x > p2.x) swap(p1, p2);
    return p1.x <= p3.x && p3.x <= p2.x &&
        (p3.y-p1.y)*(p2.x-p1.x) == (p2.y-p1.y)*(p3.x-p1.x);
}

void init() {
    for (int p1 = 0; p1 < N; p1++) {
        for (int p2 = 0; p2 < N; p2++) {
            for (int p3 = 0; p3 < N; p3++) {
                if (p3 == p1 || p3 == p2) continue;
                if (online(pts[p1], pts[p2], pts[p3])) {
                    middle[p1][p2] |= (1<<p3);
                }
            }
        }
    }
}

int solve(int mask, int last) {
    if (dp[mask][last] >= 0) return dp[mask][last];
    int &ret = dp[mask][last];
    ret = (__builtin_popcount(mask) >= 4);
    int cand = ((1<<N)-1) ^ mask;
    while (cand) {
        int p = __builtin_ctz(cand);
        bool ok = (mask & middle[last][p]) == middle[last][p];
        if (ok) (ret += solve(mask|(1<<p), p)) %= MOD;
        cand -= (1<<p);
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &pts[i].x, &pts[i].y);
    }
    init();
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans = add(ans, solve(1<<i, i));
    }
    printf("%d\n", ans);
    return 0;
}
