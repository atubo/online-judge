// https://www.luogu.org/problemnew/show/P4756
// Added Sequence

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int N, M;
int64_t A[MAXN];

struct Point {
    double x, y;
};

int side(int64_t y0, int k, double x, double y) {
    double d = y0 + k*x - y;
    return (d == 0 ? 0 : (d > 0 ? 1 : -1));
}

Point cross(const Point &p1, const Point &p2, int64_t y0, int k) {
    double kp = (p2.y-p1.y)/(p2.x-p1.x);
    double x = (p1.y-kp*p1.x-y0)/(k-kp);
    double y = y0 + k*x;
    return {x, y};
}

vector<Point> convex() {
    double xmax = 2*N;
    vector<Point> ret;
    ret.push_back({-xmax, 0});
    ret.push_back({xmax, 0});

    for (int i = 1; i <= N; i++) {
        if (side(A[i], i, ret[0].x, ret[0].y) >= 0) {
            ret.clear();
            ret.push_back({-xmax, A[i]-1.0*i*xmax});
            ret.push_back({xmax, A[i]+1.0*i*xmax});
            continue;
        }
        if (side(A[i], i, ret.back().x, ret.back().y) <= 0) continue;
        int m = ret.size();
        int lo = 0, hi = m-1;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (side(A[i], i, ret[mid].x, ret[mid].y) <= 0) lo = mid;
            else hi = mid;
        }
        if (side(A[i], i, ret[lo].x, ret[lo].y) < 0) {
            auto p = cross(ret[lo], ret[lo+1], A[i], i);
            ret.erase(ret.begin()+lo+1, ret.end());
            ret.push_back(p);
            ret.push_back({xmax, A[i]+1.0*i*xmax});
        } else {
            ret.erase(ret.begin()+lo+1, ret.end());
            ret.push_back({xmax, A[i]+1.0*i*xmax});
        }
    }

    return ret;
}

double search(const vector<Point> &c, int x) {
    const int m = c.size();
    if (x == c[0].x) return c[0].y;
    if (x == c[m-1].x) return c[m-1].y;
    int lo = 0, hi = m-1;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (c[mid].x <= x) lo = mid;
        else hi = mid;
    }
    double k = (c[lo+1].y-c[lo].y)/(c[lo+1].x-c[lo].x);
    return c[lo].y + k*(x-c[lo].x);
}

int64_t solve(const vector<Point>& top,
              const vector<Point>& bot,
              int x) {
    double t1 = search(top, x);
    double t2 = search(bot, x);
    return int64_t(t1-t2+0.1);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%ld", &A[i]);
        A[i] += A[i-1];
    }
    auto c1 = convex();
    for (int i = 1; i <= N; i++) {
        A[i] = -A[i];
    }
    auto c2 = convex();
    reverse(c2.begin(), c2.end());
    for (auto &p: c2) {
        p.x = -p.x;
        p.y = -p.y;
    }
    int64_t pre = 0;
    for (int i = 0; i < M; i++) {
        int64_t x;
        scanf("%ld", &x);
        x = (x + pre)%(4*N+1) - 2*N;
        int64_t ans = solve(c1, c2, x);
        printf("%ld\n", ans);
        pre = ans;
    }
    return 0;
}
