// https://www.luogu.org/problemnew/show/P3161
// [CQOI2012]模拟工厂

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;

struct Order {
    int t, g, m;
    bool operator < (const Order &other) const {
        return t < other.t;
    }
} orders[MAXN];

int N;

int64_t totProfit(int mask) {
    int64_t ret = 0;
    for (int i = 0; i < N; i++) {
        if ((mask>>i) & 1) ret += orders[i].m;
    }
    return ret;
}

bool check(int mask) {
    int t = 0, p = 1;
    int64_t cnt = 0;
    for (int i = -1; i < N-1; i++) {
        if (((mask >> (i+1)) & 1) == 0) continue;
        int k = INT_MAX;
        int64_t g = 0;
        for (int j = i+1; j < N; j++) {
            if (((mask >> j) & 1) == 0) continue;
            g += orders[j].g;
            int d = orders[j].t - t;
            int64_t delta = 1LL*(d-p)*(d-p) + 4LL*(p*d-(g-cnt));
            if (delta < 0) return false;
            int r = (d-p)/2.0 + sqrt(delta)/2.0;
            k = min(k, r);
            if (k < 0) return false;
        }
        cnt += 1LL * (p + k) * (orders[i+1].t - t - k) - orders[i+1].g;
        p += k;
        t = orders[i+1].t;
    }
    return true;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int t, g, m;
        scanf("%d%d%d", &t, &g, &m);
        orders[i] = {t, g, m};
    }
    sort(orders, orders+N);
    int64_t ans = 0;
    for (int mask = (1<<N)-1; mask > 0; mask--) {
        int64_t profit = totProfit(mask);
        if (profit <= ans) continue;
        if (check(mask)) ans = profit;
    }
    printf("%ld\n", ans);

    return 0;
}
