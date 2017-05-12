// https://www.luogu.org/problem/show?pid=2313
// [HNOI2005]汤姆的游戏

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10, INF = 1e30;
int N, M;

struct Point {
    Point(double x_=0, double y_=0, int id_=0): x(x_), y(y_), id(id_) {}
    double x, y;
    int id;

    bool operator < (const Point &other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return (id < other.id);
    }
};

Point pts[260000];
int cnt[260000];

struct Rect {
    Rect(double l, double r, double t, double b):
        left(l), right(r), top(t), bottom(b) {}

    double left, right, top, bottom;

    void count() const {
        Point *p = lower_bound(pts, pts+M, Point(left + EPS, -INF, -1));
        Point *q = lower_bound(pts, pts+M, Point(right, -INF, -1));
        for (Point *it = p; it != q; ++it) {
            if (isIn(*it)) cnt[it->id]++;
        }
    }

    bool isIn(const Point &p) const {
        return bottom < p.y && p.y < top;
    }
};

struct Circle {
    Circle(double x0_, double y0_, double r_): x0(x0_), y0(y0_), r(r_) {}
    double x0, y0, r;

    void count() const {
        Point *p = lower_bound(pts, pts+M, Point(x0 - r + EPS, -INF, -1));
        Point *q = lower_bound(pts, pts+M, Point(x0 + r, -INF, -1));
        for (Point *it = p; it != q; ++it) {
            if (isIn(*it)) cnt[it->id]++;
        }
    }

    bool isIn(const Point &p) const {
        double dx = p.x - x0;
        double dy = p.y - y0;
        return dx * dx + dy * dy < r * r;
    }
};

int main() {
    scanf("%d%d", &N, &M);
    vector<Rect> rect;
    vector<Circle> circle;
    char s[10];
    for (int i = 0; i < N; i++) {
        scanf("%s", s);
        if (s[0] == 'r') {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            rect.push_back(Rect(x1, x2, y2, y1));
        } else {
            double x, y, r;
            scanf("%lf%lf%lf", &x, &y, &r);
            circle.push_back(Circle(x, y, r));
        }
    }

    for (int i = 0; i < M; i++) {
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
        pts[i].id = i;
    }

    sort(pts, pts + M);

    for (const auto &r : rect) {
        r.count();
    }

    for (const auto &c : circle) {
        c.count();
    }

    for (int i = 0; i < M; i++) {
        printf("%d\n", cnt[i]);
    }

    return 0;
}
