// https://www.luogu.org/problemnew/show/P4254
// [JSOI2008]Blue Mary开公司

#include <bits/stdc++.h>
using namespace std;

// 1-indexed
class LcSegmentTree {
public:
    struct Line {
        double k, b;
        int l, r;
        int flag;
    };

    static double calc(const Line &a, int pos) {
        return a.k*pos + a.b;
    }

    static int cross(const Line &a, const Line &b) {
        return floor((a.b-b.b)/(b.k-a.k));
    }

    LcSegmentTree(int n): n_(n) {
        alloc();
    }

    ~LcSegmentTree() {
        dealloc();
    }

    void modify(double k, double b, int l, int r) {
        modify(1, 1, n_, {k, b, l, r, 1});
    }

    double query(int x) const {
        return query(1, 1, n_, x);
    }

private:
    const double eps = 1e-9;
    int n_;
    Line *sgt_;

    void alloc() {
        sgt_ = new Line[4*n_+1]{};
    }

    void dealloc() {
        delete[] sgt_;
    }

    void modify(int k, int l, int r, Line line) {
        // current range is [l, r], modify range is [a, b]
        if (line.l <= l && r <= line.r) {
            double dl = calc(line, l) - calc(sgt_[k], l);
            double dr = calc(line, r) - calc(sgt_[k], r);
            if (!sgt_[k].flag) {
                sgt_[k] = line;
            } else if (dl > eps && dr > eps) {
                sgt_[k] = line;
            } else if (dl > eps || dr > eps) {
                int mid = (l + r) / 2;
                double dm = calc(line, mid) - calc(sgt_[k], mid);
                if (fabs(dm) > eps) {
                    if (dm > eps) {
                        swap(line, sgt_[k]);
                    }
                    if (cross(line, sgt_[k]) - mid < -eps) {
                        modify(2*k, l, mid, line);
                    } else {
                        modify(2*k+1, mid+1, r, line);
                    }
                } else {
                    if (dl > eps) {
                        modify(2*k, l, mid, line);
                    } else {
                        modify(2*k+1, mid+1, r, line);
                    }
                }
            }
        } else {
            int mid = (l + r) / 2;
            if (line.l <= mid) modify(2*k, l, mid, line);
            if (mid < line.r)  modify(2*k+1, mid+1, r, line);
        }
    }

    double query(int k, int l, int r, int x) const {
        if (l == r) return calc(sgt_[k], x);
        int mid = (l + r) / 2;
        double ans = calc(sgt_[k], x);
        if (x <= mid) ans = max(ans, query(2*k, l, mid, x));
        else ans = max(ans, query(2*k+1, mid+1, r, x));
        return ans;
    }
};

const int MAXT = 50000;
int N;

int main() {
    scanf("%d", &N);
    char cmd[10];
    LcSegmentTree lc(MAXT);
    for (int i = 0; i < N; i++) {
        double s, p;
        int t;
        scanf("%s", cmd);
        if (cmd[0] == 'P') {
            scanf("%lf%lf", &s, &p);
            lc.modify(p, s-p, 1, MAXT);
        } else {
            scanf("%d", &t);
            printf("%ld\n", int64_t(lc.query(t)/100));
        }
    }

    return 0;
}
