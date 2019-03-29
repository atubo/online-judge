// https://www.luogu.org/problemnew/show/P3707
// [SDOI2017]相关分析

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    __int128_t *s_, *t_, *x_, *y_, *xy_, *xx_;
    int *type_;

public:
    SegmentTree(int N_): N(N_) {
        s_ = new __int128_t[4*N]{};
        t_ = new __int128_t[4*N]{};
        x_ = new __int128_t[4*N]{};
        y_ = new __int128_t[4*N]{};
        xy_ = new __int128_t[4*N]{};
        xx_ = new __int128_t[4*N]{};
        type_ = new int[4*N]{};
    }

    ~SegmentTree() {
        delete[] s_;
        delete[] t_;
        delete[] x_;
        delete[] y_;
        delete[] xy_;
        delete[] xx_;
        delete[] type_;
    }
    // add s, t to range [a, b]
    void add(int s, int t, int a, int b) {
        add(1, s, t, 1, N, a, b);
    }

    void modify(int s, int t, int a, int b) {
        modify(1, s, t, 1, N, a, b);
    }

    double query(int a, int b) {
        __int128_t x, y, xy, xx;
        query(1, a, b, 1, N, x, y, xy, xx);
        const int m = b - a + 1;
        double up = xy - 1.0*x*y/m;
        double down = xx - 1.0*x*x/m;
        printf("%.6f\n", up/down);
        return 0;
    }

private:
    void combine(int k) {
        x_[k] = x_[2*k] + x_[2*k+1];
        y_[k] = y_[2*k] + y_[2*k+1];
        xy_[k] = xy_[2*k] + xy_[2*k+1];
        xx_[k] = xx_[2*k] + xx_[2*k+1];
    }

    void eval(int k, int l, int r, int op, int s, int t) {
        const __int128_t ONE = 1;
        const int m = r - l + 1;
        if (op == 1) {
            xx_[k] += x_[k]*s*2 + ONE*s*s*m;
            xy_[k] += y_[k]*s + x_[k]*t + ONE*s*t*m;
            x_[k] += ONE*s*m;
            y_[k] += ONE*t*m;
        } else {
            __int128_t si = 1LL*r*(r+1)/2 - 1LL*l*(l-1)/2;
            __int128_t si2 = 1LL*r*(r+1)*(2*r+1)/6
                - 1LL*(l-1)*l*(2*l-1)/6;
            x_[k] = ONE*s*m + si;
            y_[k] = ONE*t*m + si;
            xy_[k] = ONE*s*t*m + s*si + t*si + si2;
            xx_[k] = ONE*s*s*m + s*si*2 + si2;
        }
    }

    // add s, t to range [a, b], current node range is [l, r]
    void add(int k, int s, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            eval(k, l, r, 1, s, t);
            merge(k, 1, s, t);
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) add(2*k,   s, t, l, mid, a, b);
        if (mid < b)  add(2*k+1, s, t, mid+1, r, a, b);
        combine(k);
    }

    void modify(int k, int s, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            eval(k, l, r, 2, s, t);
            merge(k, 2, s, t);
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) modify(2*k, s, t, l, mid, a, b);
        if (mid < b)  modify(2*k+1, s, t, mid+1, r, a, b);
        combine(k);
    }

    void pushDown(int k, int l, int r) {
        if (type_[k] == 0 || l == r) return;
        int mid = (l + r) / 2;
        mergeDown(k, 2*k, l, mid);
        mergeDown(k, 2*k+1, mid+1, r);
        type_[k] = 0;
        s_[k] = t_[k] = 0;
    }

    void merge(int k, int type, __int128_t s, __int128_t t) {
        if (type == 0) return;
        if (type == 1) {
            if (type_[k] == 0) {
                type_[k] = 1;
                s_[k] = s;
                t_[k] = t;
            } else {
                s_[k] += s;
                t_[k] += t;
            }
        } else {
            type_[k] = 2;
            s_[k] = s;
            t_[k] = t;
        }
    }

    void mergeDown(int k, int j, int l, int r) {
        eval(j, l, r, type_[k], s_[k], t_[k]);
        merge(j, type_[k], s_[k], t_[k]);
    }

    // query range sum in [a, b], current node is [L, R]
    void query(int k, int a, int b, int L, int R,
                  __int128_t &x, __int128_t &y,
                  __int128_t &xy, __int128_t &xx) {
        x = y = xy = xx = 0;
        if (!k) return;
        if (b < L || a > R) return;
        pushDown(k, L, R);
        if (a <= L && R <= b) {
            x = x_[k];
            y = y_[k];
            xy = xy_[k];
            xx = xx_[k];
            return;
        }
        __int128_t x1=0, x2=0, y1=0, y2=0, xy1=0, xy2=0, xx1=0, xx2=0;
        int mid = (L + R) / 2;
        if (a <= mid) query(2*k, a, b, L, mid, x1, y1, xy1, xx1);
        if (mid < b)  query(2*k+1, a, b, mid+1, R, x2, y2, xy2, xx2);
        x = x1 + x2;
        y = y1 + y2;
        xy = xy1 + xy2;
        xx = xx1 + xx2;
    }
};

const int MAXN = 1e5+10;
int N, M;
int X[MAXN], Y[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    SegmentTree st(N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &X[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &Y[i]);
    }
    for (int i = 1; i <= N; i++) {
        st.add(X[i], Y[i], i, i);
    }
    for (int i = 0; i < M; i++) {
        int op, l, r, s, t;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            st.query(l, r);
        } else if (op == 2) {
            scanf("%d%d", &s, &t);
            st.add(s, t, l, r);
        } else {
            scanf("%d%d", &s, &t);
            st.modify(s, t, l, r);
        }
    }
    return 0;
}
