// https://www.luogu.org/problemnew/show/P2698
// [USACO12MAR]花盆Flowerpot

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, D;

struct WaterDrop {
    int x, y;
    bool operator < (const WaterDrop &other) {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return y < other.y;
    }
} W[MAXN];

bool check(int mid) {
    int ans = INT_MIN;
    deque<WaterDrop> qh, ql;
    for (int i = 0; i < N; i++) {
        while (!qh.empty() && qh.front().x < W[i].x-mid) qh.pop_front();
        while (!ql.empty() && ql.front().x < W[i].x-mid) ql.pop_front();
        while (!qh.empty() && qh.back().y <= W[i].y) qh.pop_back();
        while (!ql.empty() && ql.back().y >= W[i].y) ql.pop_back();
        qh.push_back(W[i]);
        ql.push_back(W[i]);
        ans = max(ans, qh.front().y-ql.front().y);
    }
    return ans >= D;
}


int main() {
    scanf("%d%d", &N, &D);
    int maxy = INT_MIN, miny = INT_MAX;
    int maxx = INT_MIN, minx = INT_MAX;
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        maxx = max(maxx, x);
        minx = min(minx, x);
        maxy = max(maxy, y);
        miny = min(miny, y);
        W[i] = {x, y};
    }
    if (maxy - miny < D) {
        printf("-1");
        return 0;
    }
    sort(W, W+N);

    int lo = -1, hi = maxx - minx;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d", hi);
    return 0;
}
