// https://www.luogu.org/problemnew/show/P4040
// [AHOI2014/JSOI2014]宅男计划

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
int64_t M, F;
int N;

struct Food {
    int64_t p, s;
    bool operator < (const Food &other) const {
        if (s < other.s) return true;
        if (s > other.s) return false;
        return p > other.p;
    }
} foods[MAXN];

struct Point {
    int64_t x, y;
};

int64_t solve(const vector<Point> &pts, int64_t y, int64_t &r, int &idx) {
    const int n = pts.size();
    if (pts.back().y <= y) {
        r = y - pts.back().y;
        idx = n;
        return pts.back().x;
    }
    int64_t x0 = 0, y0 = 0;
    for (int i = 0; i < n; i++) {
        auto pt = pts[i];
        if (pt.y <= y) {
            x0 = pt.x;
            y0 = pt.y;
        } else {
            int64_t p = (pt.y-y0)/(pt.x-x0);
            r = (y-y0) % p;
            idx = i;
            return x0 + (y-y0)/p;
        }
    }
    assert(false);
    return -1;
}

int64_t solve2(const vector<Point> &pts, int64_t k, int64_t s, int64_t t,
               int idx) {
    const int n = pts.size();
    if (idx == n) return 0;
    int64_t x0 = (idx == 0 ? 0 : pts[idx-1].x);
    int64_t y0 = (idx == 0 ? 0 : pts[idx-1].y);
    int64_t s0 = s;
    int64_t ans = 0;
    for (int i = idx; i < n; i++) {
        auto pt = pts[i];
        int64_t p = (pt.y-y0)/(pt.x-x0);
        if (k >= 1.0*p*(pt.x-s)*t) {
            k -= p*(pt.x-s)*t;
            s = pt.x;
            x0 = pt.x;
            y0 = pt.y;
            ans += (pt.x-s) * t;
        } else {
            ans += k/p;
            return ans;
        }
    }
    return t*(pts.back().x - s0);
}


int64_t survive(const vector<Point> &pts, int64_t t) {
    int64_t m = M - t*F;
    if (m <= 0) return 0;
    int64_t r;
    int idx;
    int64_t w = m / t;
    int64_t k = m % t;

    int64_t s1 = solve(pts, w, r, idx);
    int64_t ans = t * s1;
    k += r * t;
    ans += solve2(pts, k, s1, t, idx);
    return ans;
}


int main() {
    scanf("%ld%ld%d", &M, &F, &N);
    for (int i = 0; i < N; i++) {
        int64_t p, s;
        scanf("%ld%ld", &p, &s);
        foods[i] = {p, s+1};
    }
    sort(foods, foods+N);
    vector<Food> cand;
    for (int i = 0; i < N; i++) {
        while (!cand.empty() && cand.back().p >= foods[i].p) {
            cand.pop_back();
        }
        cand.push_back(foods[i]);
    }

    vector<Point> pts;
    int64_t x = 0;
    int64_t y = 0;
    for (Food f: cand) {
        double tmp = y + 1.0 * f.p * (f.s - x);
        if (tmp > M) {
            int64_t smax = (M-y)/f.p + x;
            y += 1LL * f.p * (smax - x);
            pts.push_back({smax, y});
            break;
        }
        y += 1LL * f.p * (f.s - x);
        x = f.s;
        pts.push_back({x, y});
    }

    int64_t lo = 1;
    int64_t hi = (F == 0 ? M+1:M/F+1);
    while (lo <= hi-3) {
        int64_t m1 = lo + (hi-lo)/3;
        int64_t m2 = hi - (hi-lo)/3;
        int64_t t1 = survive(pts, m1);
        int64_t t2 = survive(pts, m2);
        if (t1 >= t2) hi = m2;
        else lo = m1;
    }
    int64_t ans = INT_MIN;
    for (int64_t i = lo; i <= hi; i++) {
        ans = max(ans, survive(pts, i));
    }
    printf("%ld", ans);

    return 0;
}
