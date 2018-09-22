// https://www.luogu.org/problemnew/show/P2202
// [USACO13JAN]方块重叠Square Overlap

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;

struct Point {
    Point(int xx, int yy): x(xx), y(yy) {}
    int x, y;
    bool operator < (const Point &other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return (y < other.y);
    }
};

struct Event {
    int x, y, t;
    bool operator < (const Event &other) const {
        if (y < other.y) return true;
        if (y > other.y) return false;
        if (t < other.t) return true;
        if (t > other.t) return false;
        return (x < other.x);
    }
} events[2*MAXN];

int N, K;

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        events[2*i] = {x-K/2, y-K/2, 1};
        events[2*i+1] = {x-K/2, y+K/2, 0};
    }
    sort(events, events+2*N);

    bool found = false;
    int64_t ans = 0;
    set<Point> pts;
    for (int i = 0; i < 2*N; i++) {
        int x = events[i].x, y = events[i].y;
        if (events[i].t == 0) {
            auto it = pts.find(Point{x, y-K});
            pts.erase(it);
        } else {
            auto it = pts.upper_bound(Point(x-K, INT_MAX));
            if (!((it == pts.end() || it->x >= x+K))) {
                if (found) {
                    printf("-1\n");
                    return 0;
                }
                found = true;
                ans = 1LL * (K - abs(it->x - x)) * (K - abs(it->y - y));
                ++it;
                if (it != pts.end() && it->x < x + K) {
                    printf("-1\n");
                    return 0;
                }
            }
            pts.insert(Point(x, y));
        }
    }
    printf("%ld\n", ans);

    return 0;
}
