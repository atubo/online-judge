// https://www.luogu.org/problemnew/show/P1354
// 房间最短路问题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 22;
int N;

struct Wall {
    double x, a1, b1, a2, b2;
} walls[MAXN];

struct Point {
    double x, y;
    double d;
} points[4*MAXN];

double dist(const Point &p, const Point &q) {
    double x1 = p.x, y1 = p.y;
    double x2 = q.x, y2 = q.y;
    double dx = fabs(x1 - x2);
    double dy = fabs(y1 - y2);
    return sqrt(dx*dx + dy*dy);
}

bool can_pass(const Point &u, const Point &v, const Wall &w) {
    double x1 = u.x, y1 = u.y;
    double x2 = v.x, y2 = v.y;
    double xw = w.x;

    double y = y1 + (y2-y1)/(x2-x1) * (xw-x1);
    return (w.a1 <= y && y <= w.b1) || (w.a2 <= y && y <= w.b2);
}

bool reachable(const Point &u, const Point &v, int p, int q) {
    for (int i = p; i <= q; i++) {
        if (!can_pass(u, v, walls[i])) return false;
    }
    return true;
}

void process_point(int w, Point &pt) {
    if (reachable(points[0], pt, 0, w-1)) {
        pt.d = min(pt.d, dist(points[0], pt));
    }
    for (int wp = 0; wp < w; wp++) {
        for (int i = 1; i <= 4; i++) {
            const Point &q = points[4*wp+i];
            if (reachable(q, pt, wp+1, w-1)) {
                pt.d = min(pt.d, q.d + dist(q, pt));
            }
        }
    }
}

void process_wall(int w) {
    points[4*w+1] = {walls[w].x, walls[w].a1, 1e9};
    process_point(w, points[4*w+1]);
    points[4*w+2] = {walls[w].x, walls[w].b1, 1e9};
    process_point(w, points[4*w+2]);
    points[4*w+3] = {walls[w].x, walls[w].a2, 1e9};
    process_point(w, points[4*w+3]);
    points[4*w+4] = {walls[w].x, walls[w].b2, 1e9};
    process_point(w, points[4*w+4]);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        double x, a1, b1, a2, b2;
        scanf("%lf%lf%lf%lf%lf", &x, &a1, &b1, &a2, &b2);
        walls[i] = {x, a1, b1, a2, b2};
    }
    points[0] = {0, 5, 0};
    for (int i = 0; i < N; i++) {
        process_wall(i);
    }
    points[4*N+1] = {10, 5, 1e9};
    process_point(N, points[4*N+1]);
    printf("%.2f\n", points[4*N+1].d);
    return 0;
}
