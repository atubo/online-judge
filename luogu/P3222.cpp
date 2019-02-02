// https://www.luogu.org/problemnew/show/P3222
// [HNOI2012]射箭

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

struct Line {
    int64_t a, b, c;
    bool operator < (const Line &other) const {
        return 1.0*a*other.b > 1.0*b*other.a;
    }
} LB[MAXN], UB[MAXN], bot[MAXN], top[MAXN], tot[2*MAXN];

struct Point {
    double x, y;
};

struct Data {
    Point p;
    Line line;
} st[2*MAXN];

Point cross(const Line &l1, const Line &l2) {
    double a1 = l1.a, b1 = l1.b, c1 = l1.c;
    double a2 = l2.a, b2 = l2.b, c2 = l2.c;
    double d = a2*b1 - a1*b2;
    double x = (c2*b1 - c1*b2)/d;
    double y = (c1*a2 - c2*a1)/d;
    return {x, y};
}

int side(const Line &l, const Point &p) {
    const double EPS = 1e-9;
    double r = l.a * p.x + l.b * p.y - l.c;
    return (r > EPS ? 1 : (r < -EPS ? -1 : 0));
}

int N;

bool feasible(int mid) {
    for (int i = 0; i < mid; i++) {
        bot[i] = LB[i];
        top[i] = UB[i];
    }
    sort(bot, bot+mid);
    sort(top, top+mid);
    for (int i = 0; i < mid; i++) {
        tot[i] = top[i];
    }
    for (int i = 0; i < mid; i++) {
        tot[i+mid] = bot[i];
    }
    int sz = 0;
    st[sz++] = {{0, 0}, {-1, 0, 0}};
    for (int i = 0; i < 2*mid; i++) {
        while (sz > 0 && side(tot[i], st[sz-1].p) < 0) sz--;
        if (sz == 0) return false;
        auto p = cross(st[sz-1].line, tot[i]);
        if (p.x > 0) continue;
        st[sz++] = {p, tot[i]};
    }
    for (int i = 0; i < sz; i++) {
        if (st[i].p.x < 0) return true;
    }
    return false;
}


int main() {
    scanf("%d", &N);
    int hi = N+1;
    set<int> mark;
    for (int i = 0; i < N; i++) {
        int x, y1, y2;
        scanf("%d%d%d", &x, &y1, &y2);
        LB[i] = {1LL*x*x, x, y1};
        UB[i] = {-1LL*x*x, -x, -y2};
        if (mark.count(x) > 0 && hi == N+1) hi = i+1;
    }
    int lo = 1;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid;
    }
    printf("%d\n", lo);
    return 0;
}
