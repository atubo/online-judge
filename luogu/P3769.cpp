// https://www.luogu.org/problem/P3769
// [CH弱省胡策R2]TATT

#include <bits/stdc++.h>
using namespace std;

short dim;
struct Point {
    int x[3], w;
    bool operator < (const Point &other) const {
        if (x[dim] != other.x[dim]) return x[dim] < other.x[dim];
        for (int i = 0; i < 3; i++) {
            if (x[i] != other.x[i]) return x[i] < other.x[i];
        }
        return false;
    }
};

// dynamically rebalance
template<short K>
class KdTree3 {
    friend class KdTree3Test;
public:
    //using Point = PointT<K>;
    struct Cmp {
        Cmp(int d): idx(d) {}
        bool operator () (const Point &a, const Point &b) const {
            return a.x[idx] < b.x[idx];
        }
        int idx;
    };

    KdTree3(int n): n_(n) {
        alloc();
        for (int i = 0; i < K; i++) {
            max_[i][0] = INT_MIN;
            min_[i][0] = INT_MAX;
        }
    }

    ~KdTree3() {
        dealloc();
    }

    void insert(const Point &p) {
        auto bad = insert(root_, p, 0);
        if (bad.first) rebuild(bad);
    }

    int query(int *x) const {
        int ans = 0;
        query(1, x, ans);
        return ans;
    }

    void print() const {
        print('r', root_, 0);
    }

private:
    constexpr static double alpha = 0.75;
    const int n_;
    int *lc_, *rc_;
    int *size_, *maxwt_;
    int *max_[K], *min_[K];
    Point *d_;  // point on the node
    int curr_ = 0;
    int root_ = 0;
    Point *buf_;
    int *idx_;
    int top_ = 0;

    void alloc() {
        const int np = n_+1;
        lc_ = new int[np]{};
        rc_ = new int[np]{};
        size_ = new int[np]{};
        maxwt_ = new int[np]{};
        for (int i = 0; i < K; i++) {
            max_[i] = new int[np]{};
            min_[i] = new int[np]{};
        }
        d_ = new Point[np]{};
        buf_ = new Point[np]{};
        idx_ = new int[np]{};
    }

    void dealloc() {
        delete[] lc_;
        delete[] rc_;
        delete[] size_;
        delete[] maxwt_;
        for (int i = 0; i < K; i++) {
            delete[] max_[i];
            delete[] min_[i];
        }
        delete[] d_;
        delete[] buf_;
        delete[] idx_;
    }

    void pushup(int k) {
        int lc = lc_[k], rc = rc_[k];
        size_[k] = 1 + size_[lc] + size_[rc];
        maxwt_[k] = max(max(maxwt_[lc], maxwt_[rc]), d_[k].w);
        for (int i = 0; i < K; i++) {
            max_[i][k] = max(max(max_[i][lc], max_[i][rc]), d_[k].x[i]);
            min_[i][k] = min(min(min_[i][lc], min_[i][rc]), d_[k].x[i]);
        }
    }

    bool unbalanced(int k) const {
        int lc = lc_[k], rc = rc_[k];
        return size_[lc] > size_[k]*alpha ||
            size_[rc] > size_[k]*alpha;
    }

    void setLeaf(int k) {
        lc_[k] = rc_[k] = 0;
        size_[k] = 1;
        for (int i = 0; i < K; i++) {
            max_[i][k] = min_[i][k] = d_[k].x[i];
        }
        maxwt_[k] = d_[k].w;
    }

    void spawn(int &k, const Point &p) {
        k = ++curr_;
        d_[k] = p;
        setLeaf(k);
        pushup(k);
    }

    pair<int*, int> insert(int &k, const Point &p, int d) {
        if (k == 0) {
            spawn(k, p);
            return make_pair((int*)NULL, d);
        }
        int &c = p.x[d] < d_[k].x[d] ? lc_[k] : rc_[k]; 
        auto bad = insert(c, p, (d+1)%K);
        pushup(k);
        if (unbalanced(k)) {
            bad = make_pair(&k, d);
        }
        return bad;
    }

    void traverse(int k) {
        if (k == 0) return;
        idx_[top_] = k;
        buf_[top_] = d_[k];
        top_++;
        traverse(lc_[k]);
        traverse(rc_[k]);
    }

    int build(int l, int r, int d, int &curr) {
        if (l > r) return 0;
        int mid = (l + r) / 2;
        dim = d;
        nth_element(buf_+l, buf_+mid, buf_+r+1);
        d_[idx_[curr++]] = buf_[mid];
        int k = idx_[curr-1];
        if (l == r) {
            setLeaf(k);
            return k;
        }
        lc_[k] = build(l, mid-1, (d+1)%K, curr);
        rc_[k] = build(mid+1, r, (d+1)%K, curr);
        pushup(k);
        return k;
    }

    void rebuild(const pair<int*, int> &bad) {
        int k = *bad.first;
        int d = bad.second;
        top_ = 0;
        traverse(k);
        int curr = 0;
        build(0, top_-1, d, curr);
    }

    void query(int k, int *x, int &ans) const {
        if (k == 0) return;
        for (int i = 0; i < K; i++) {
            if (min_[i][k] > x[i]) return;
        }
        int found = false;
        for (int i = 0; i < K; i++) {
            if (max_[i][k] > x[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            ans = max(ans, maxwt_[k]);
            return;
        }
        found = false;
        for (int i = 0; i < K; i++) {
            if (d_[k].x[i] > x[i]) {
                found = true;
                break;
            }
        }
        if (!found) ans = max(ans, d_[k].w);
        if (maxwt_[lc_[k]] > ans) query(lc_[k], x, ans);
        if (maxwt_[rc_[k]] > ans) query(rc_[k], x, ans);
    }
};

const int MAXN = 50010;
int N;
struct Pt {
    int x[4];
    bool operator < (const Pt &other) const {
        for (int i = 0; i < 4; i++) {
            if (x[i] != other.x[i]) return x[i] < other.x[i];
        }
        return false;
    }
} P[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        P[i].x[0] = a;
        P[i].x[1] = b;
        P[i].x[2] = c;
        P[i].x[3] = d;
    }
    sort(P+1, P+N+1);

    int ret = 0;
    KdTree3<3> kd(N);
    kd.insert(Point{{P[1].x[1], P[1].x[2], P[1].x[3]}, 1});
    for (int i = 2; i <= N; i++) {
        int x[3] = {P[i].x[1], P[i].x[2], P[i].x[3]};
        int w = kd.query(x) + 1;
        ret = max(ret, w);
        kd.insert(Point{{P[i].x[1], P[i].x[2], P[i].x[3]}, w});
    }
    printf("%d\n", ret);
    return 0;
}
