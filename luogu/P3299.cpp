// https://www.luogu.org/problemnew/show/P3299
// [SDOI2013]保护出题人

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int64_t x, y;
};

int64_t N, D;

bool isConvex(const Point &p1, const Point &p2, const Point &p3) {
    auto dx1 = p2.x - p1.x, dy1 = p2.y - p1.y;
    auto dx2 = p3.x - p2.x, dy2 = p3.y - p2.y;
    return double(dy1)*dx2 < double(dy2)*dx1;
}

double slope(int64_t a, int64_t x, const Point &pt, const Point &pt0) {
    int64_t x0 = pt0.x - x;
    int64_t y0 = pt0.y - a;
    return 1.0*(pt.y-y0) / (pt.x-x0);
}

double solve(int64_t a, int64_t x, const deque<Point> &pts) {
    int lo = 0, hi = pts.size()-1;
    while (lo < hi-2) {
        int d = (hi-lo)/3;
        int m1 = lo + d;
        int m2 = hi - d;
        if (slope(a, x, pts[m1], pts[0]) <
            slope(a, x, pts[m2], pts[0])) lo = m1;
        else hi = m2;
    }
    double ans = -1;
    for (int i = lo; i <= hi; i++) {
        ans = max(ans, slope(a, x, pts[i], pts[0]));
    }
    return ans;
}

int main() {
    scanf("%ld%ld", &N, &D);
    deque<Point> pts;
    int64_t tot = 0;
    double ans = 0;
    for (int i = 0; i < N; i++) {
        int64_t a, x;
        scanf("%ld%ld", &a, &x);

        Point curr{-1LL*i*D, -tot};
        while (pts.size() > 1 &&
               isConvex(curr, pts[0], pts[1])) pts.pop_front();
        pts.push_front(curr);
        auto attack = solve(a, x, pts);
        ans += attack;
        tot += a;
    }

    printf("%ld\n", int64_t(ans+0.5));

    return 0;
}
