// https://www.luogu.org/problemnew/show/P2218
// [HAOI2007]覆盖问题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;
int N;
struct Point {
    int x, y;
} P1[MAXN], P2[MAXN], Q[MAXN];
int XMIN, YMIN, XMAX, YMAX;

bool solve1(Point* pts, int l) {
    int xmin = INT_MAX, ymin = INT_MAX;
    int xmax = INT_MIN, ymax = INT_MIN;
    for (int i = 0; i < N; i++) {
        int x = pts[i].x;
        int y = pts[i].y;
        if ((x <= XMIN+l && y <= YMIN+l) || (x >= XMAX-l && y >= YMAX-l)) {
            continue;
        }
        xmin = min(xmin, x);
        ymin = min(ymin, y);
        xmax = max(xmax, x);
        ymax = max(ymax, y);
    }

    bool ret = true;
    if (xmin != INT_MAX) {
        ret = (xmax <= xmin+l && ymax <= ymin+l);
    }
    return ret;
}

bool solve2(Point *pts, int l) {
    int sz = 0;
    int xl = INT_MAX;
    for (int i = 0; i < N; i++) {
        int x = pts[i].x;
        int y = pts[i].y;
        if (x > XMIN+l || y > YMIN+l) {
            Q[sz++] = {x, y};
            xl = min(xl, x);
        }
    }
    if (sz == 0) return true;

    int xmin = INT_MAX, ymin = INT_MAX;
    int xmax = INT_MIN, ymax = INT_MIN;
    for (int i = 0; i < sz; i++) {
        int x = Q[i].x;
        int y = Q[i].y;
        if ((x <= xl+l && y >= YMAX-l)) continue;
        xmin = min(xmin, x);
        ymin = min(ymin, y);
        xmax = max(xmax, x);
        ymax = max(ymax, y);
    }
    bool ret = true;
    if (xmin != INT_MAX) {
        ret = (xmax <= xmin+l && ymax <= ymin+l);
    }
    return ret;
}

bool solve3(Point *pts, int l) {
    int sz = 0;
    int xr = INT_MIN;
    for (int i = 0; i < N; i++) {
        int x = pts[i].x;
        int y = pts[i].y;
        if (x < XMAX-l || y < YMAX-l) {
            Q[sz++] = {x, y};
            xr = max(xr, x);
        }
    }
    if (sz == 0) return true;

    int xmin = INT_MAX, ymin = INT_MAX;
    int xmax = INT_MIN, ymax = INT_MIN;
    for (int i = 0; i < sz; i++) {
        int x = Q[i].x;
        int y = Q[i].y;
        if ((x >= xr-l && y <= YMIN+l)) continue;
        xmin = min(xmin, x);
        ymin = min(ymin, y);
        xmax = max(xmax, x);
        ymax = max(ymax, y);
    }
    bool ret = true;
    if (xmin != INT_MAX) {
        ret = (xmax <= xmin+l && ymax <= ymin+l);
    }
    return ret;
}


int main() {
    scanf("%d", &N);
    XMIN = YMIN = INT_MAX;
    XMAX = YMAX = INT_MIN;
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        P1[i] = {x, y};
        XMIN = min(XMIN, x);
        YMIN = min(YMIN, y);
        XMAX = max(XMAX, x);
        YMAX = max(YMAX, y);
    }

    for (int i = 0; i < N; i++) {
        int x = P1[i].x;
        int y = P1[i].y;
        P2[i] = {XMIN+XMAX-x, y};
    }
    int lo = 0, hi = max(XMAX-XMIN, YMAX-YMIN);
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (solve1(P1, mid) || solve2(P1, mid) || solve3(P1, mid) ||
            solve1(P2, mid) || solve2(P2, mid) || solve3(P2, mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    printf("%d\n", hi);
    return 0;
}
