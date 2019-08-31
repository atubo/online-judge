// https://www.luogu.org/problem/P4357
// [CQOI2016]K远点对

#include <bits/stdc++.h>
using namespace std;

// 1-indexed
class KdTree {
    struct Point {
        int x[2];
    };

    struct Cmp {
        Cmp(int x): idx(x) {}
        bool operator ()(const Point &a, const Point &b) const {
            return a.x[idx] < b.x[idx];
        }
        int idx;
    };

    int *lc_, *rc_;
    Point *d_;
    int *maxx_, *minx_, *maxy_, *miny_;
    const int n_;
    int cnt_ = 0;

public:
    KdTree(int n, int k): n_(n) {
        alloc();
        for (int i = 0; i < 2*k; i++) q_.push(0);
    }

    ~KdTree() {
        dealloc();
    }

    int build(int l, int r) {
        if (l > r) return 0;
        int k = ++cnt_;
        if (l == r) {
            d_[k] = pt[l];
            pushup(k);
            return k;
        }
        int mid = (l + r) / 2;
        int dim = get(l, r);
        nth_element(pt+l, pt+mid, pt+r+1, Cmp(dim));
        d_[k] = pt[mid];
        lc_[k] = build(l, mid-1);
        rc_[k] = build(mid+1, r);
        pushup(k);
        return k;
    }

    void query(int k, const Point &p) {
        int64_t dl = -1, dr = -1;
        int lc = lc_[k], rc = rc_[k];
        if (lc) dl = g(p, lc);
        if (rc) dr = g(p, rc);
        int64_t di = f(p, d_[k]);
        if (q_.top() < di) {
            q_.pop();
            q_.push(di);
        }
        if (dl > dr) {
            if (q_.top() < dl) query(lc, p);
            if (q_.top() < dr) query(rc, p);
        } else {
            if (q_.top() < dr) query(rc, p);
            if (q_.top() < dl) query(lc, p);
        }
    }

    Point *pt;
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> q_;

private:
    void alloc() {
        lc_ = new int[n_+1]{};
        rc_ = new int[n_+1]{};
        pt = new Point[n_+1]{};
        d_ = new Point[n_+1]{};
        maxx_ = new int[n_+1]{};
        minx_ = new int[n_+1]{};
        maxy_ = new int[n_+1]{};
        miny_ = new int[n_+1]{};
    }

    void dealloc() {
        delete[] lc_;
        delete[] rc_;
        delete[] pt;
        delete[] d_;
        delete[] maxx_;
        delete[] minx_;
        delete[] maxy_;
        delete[] miny_;
    }

    int get(int l, int r) const {
        double sx = 0, sx2 = 0, sy = 0, sy2 = 0, d = r-l+1;
        for (int i = l; i <= r; i++) {
            sx += pt[i].x[0];
            sy += pt[i].x[1];
            sx2 += sqr(pt[i].x[0]);
            sy2 += sqr(pt[i].x[1]);
        }
        sx = sx2*d - sx*sx;
        sy = sy2*d - sy*sy;
        if (sx > sy) return 0;
        return 1;
    }

    void pushup(int k) {
        maxx_[k] = minx_[k] = d_[k].x[0];
        maxy_[k] = miny_[k] = d_[k].x[1];
        int lc = lc_[k], rc = rc_[k];
        if (lc) {
            maxx_[k] = max(maxx_[k], maxx_[lc]);
            minx_[k] = min(minx_[k], minx_[lc]);
            maxy_[k] = max(maxy_[k], maxy_[lc]);
            miny_[k] = min(miny_[k], miny_[lc]);
        }
        if (rc) {
            maxx_[k] = max(maxx_[k], maxx_[rc]);
            minx_[k] = min(minx_[k], minx_[rc]);
            maxy_[k] = max(maxy_[k], maxy_[rc]);
            miny_[k] = min(miny_[k], miny_[rc]);
        }
    }

    int64_t sqr(int x) const {return 1LL*x*x;}
    int64_t f(const Point &a, const Point &b) const {
        return sqr(a.x[0]-b.x[0]) + sqr(a.x[1]-b.x[1]);
    }
    int64_t g(const Point &a, int k) const {
        return max(sqr(a.x[0]-maxx_[k]), sqr(a.x[0]-minx_[k])) +
            max(sqr(a.x[1]-maxy_[k]), sqr(a.x[1]-miny_[k]));
    }
};

int N, K;

int main() {
    scanf("%d%d", &N, &K);
    KdTree kt(N, K);
    for (int i = 1; i <= N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        kt.pt[i].x[0] = x;
        kt.pt[i].x[1] = y;
    }
    kt.build(1, N);
    for (int i = 1; i <= N; i++) {
        kt.query(1, kt.pt[i]);
    }
    printf("%ld\n", kt.q_.top());

    return 0;
}
