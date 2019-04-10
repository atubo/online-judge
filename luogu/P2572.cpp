// https://www.luogu.org/problemnew/show/P2572
// [SCOI2010]序列操作

#include <bits/stdc++.h>
using namespace std;

struct Data {
    int x, y, z, n;
    void merge(const Data& other) {
        int zt = y + other.x;
        if (x == n) x += other.x;
        if (other.y == other.n) y += other.n;
        else y = other.y;
        z = max(max(z, other.z), zt);
        n += other.n;
    }
};

// note it's 1-indexed
class SegmentTree {
    int N;
    int *b_, *r_;
    int *x1_, *y1_, *z1_, *s1_, *x0_, *y0_, *z0_;

public:
    SegmentTree(int N_): N(N_) {
        b_ = new int[4*N]{};
        r_ = new int[4*N]{};
        x1_ = new int[4*N]{};
        y1_ = new int[4*N]{};
        z1_ = new int[4*N]{};
        s1_ = new int[4*N]{};
        x0_ = new int[4*N]{};
        y0_ = new int[4*N]{};
        z0_ = new int[4*N]{};
    }

    ~SegmentTree() {
        delete[] b_;
        delete[] r_;
        delete[] x1_;
        delete[] y1_;
        delete[] z1_;
        delete[] s1_;
        delete[] x0_;
        delete[] y0_;
        delete[] z0_;
    }

    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    void inverse(int a, int b) {
        inverse(1, 1, N, a, b);
    }

    int query(int a) {
        return query(1, 1, N, a);
    }

    int queryTotal(int a, int b) {
        return queryTotal(1, 1, N, a, b);
    }

    int queryConsecutive(int a, int b) {
        return queryConsecutive(1, 1, N, a, b).z;
    }

    void build(int *arr) {
        build(1, 1, N, arr);
    }

private:
    void build(int k, int l, int r, int *arr) {
        if (l == r) {
            x1_[k] = y1_[k] = z1_[k] = s1_[k] = arr[l];
            x0_[k] = y0_[k] = z0_[k] = 1 - arr[l];
            b_[k] = -1; r_[k] = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(2*k, l, mid, arr);
        build(2*k+1, mid+1, r, arr);
        pushUp(k, l, r);
        b_[k] = -1;
        r_[k] = 0;
    }

    void mergeDown(int b, int inv, int k, int l, int r) {
        if (b == -1 && inv == 0) return;
        const int n = r - l + 1;
        if (b == 0) {
            assert(inv == 0);
            x0_[k] = y0_[k] = z0_[k] = n;
            x1_[k] = y1_[k] = z1_[k] = s1_[k] = 0;
        } else if (b == 1) {
            assert(inv == 0);
            x0_[k] = y0_[k] = z0_[k] = 0;
            x1_[k] = y1_[k] = z1_[k] = s1_[k] = n;
        } else {
            swap(x0_[k], x1_[k]);
            swap(y0_[k], y1_[k]);
            swap(z0_[k], z1_[k]);
            s1_[k] = n - s1_[k];
        }
    }

    void merge(int b, int inv, int k) {
        if (b == -1 && inv == 0) return;
        if (b == 0) {
            assert(inv == 0);
            b_[k] = 0;
            r_[k] = 0;
        } else if (b == 1) {
            assert(inv == 0);
            b_[k] = 1;
            r_[k] = 0;
        } else {
            if (b_[k] != -1) {
                b_[k] = 1 - b_[k];
                assert(r_[k] == 0);
                r_[k] = 0;
            } else {
                r_[k] = 1 ^ r_[k];
            }
        }
    }

    void doPushUp(int x1, int y1, int z1,
                  int x2, int y2, int z2,
                  int n1, int n2,
                  int &x, int &y, int &z) {
        if (x1 == n1) x = n1 + x2;
        else x = x1;
        if (y2 == n2) y = n2 + y1;
        else y = y2;
        z = max(max(z1, z2), y1+x2);
    }

    void pushUp(int k, int l, int r) {
        const int lc = 2*k, rc = lc+1;
        const int mid = (l + r) / 2;
        doPushUp(x1_[lc], y1_[lc], z1_[lc],
                 x1_[rc], y1_[rc], z1_[rc],
                 mid-l+1, r-mid,
                 x1_[k], y1_[k], z1_[k]);

        doPushUp(x0_[lc], y0_[lc], z0_[lc],
                 x0_[rc], y0_[rc], z0_[rc],
                 mid-l+1, r-mid,
                 x0_[k], y0_[k], z0_[k]);

        s1_[k] = s1_[lc] + s1_[rc];
    }

    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            mergeDown(t, 0, k, l, r);
            merge(t, 0, k);
            return;
        }
        if (l == r) return;
        const int lc = 2*k, rc = lc+1;
        int mid = (l + r) / 2;
        if (a <= mid) update(lc, t, l, mid, a, b);
        if (mid < b)  update(rc, t, mid+1, r, a, b);
        pushUp(k, l, r);
    }

    void pushDown(int k, int l, int r) {
        if (l == r) return;
        const int lc = 2*k, rc = lc+1;
        int mid = (l + r) / 2;
        mergeDown(b_[k], r_[k], lc, l, mid);
        mergeDown(b_[k], r_[k], rc, mid+1, r);
        merge(b_[k], r_[k], lc);
        merge(b_[k], r_[k], rc);

        b_[k] = -1;
        r_[k] = 0;
    }

    void inverse(int k, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            mergeDown(-1, 1, k, l, r);
            merge(-1, 1, k);
            return;
        }
        if (l == r) return;
        const int lc = 2*k, rc = lc+1;
        const int mid = (l + r) / 2;
        if (a <= mid) inverse(lc, l, mid, a, b);
        if (mid < b)  inverse(rc, mid+1, r, a, b);
        pushUp(k, l, r);
    }

    int query(int k, int l, int r, int a) {
        pushDown(k, l, r);
        if (l == r && l == a) return s1_[k];
        int mid = (l + r) / 2;
        if (a <= mid) return query(2*k, l, mid, a);
        else  return query(2*k+1, mid+1, r, a);
    }

    int queryTotal(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return s1_[k];
        int sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum += queryTotal(2*k, l, mid, a, b);
        if (mid < b) sum += queryTotal(2*k+1, mid+1, r, a, b);
        return sum;
    }

    Data queryConsecutive(int k, int l, int r, int a, int b) {
        if (!k) return {0, 0, 0, 0};
        if (b < l || a > r) return {0, 0, 0, 0};
        pushDown(k, l, r);
        if (a <= l && r <= b) return {x1_[k], y1_[k], z1_[k], r-l+1};
        Data ret = {0, 0, 0, 0};
        int mid = (l + r) / 2;
        if (a <= mid) ret.merge(queryConsecutive(2*k, l, mid, a, b));
        if (mid < b) ret.merge(queryConsecutive(2*k+1, mid+1, r, a, b));
        return ret;
    }
};

const int MAXN = 1e5+10;
int N, M;
int A[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    SegmentTree st(N);
    st.build(A);

    for (int i = 0; i < M; i++) {
        int op, a, b;
        scanf("%d%d%d", &op, &a, &b);
        a++; b++;
        if (op < 2) {
            st.update(op, a, b);
        } else if (op == 2) {
            st.inverse(a, b);
        } else if (op == 3) {
            printf("%d\n", st.queryTotal(a, b));
        } else {
            printf("%d\n", st.queryConsecutive(a, b));
        }
    }

    return 0;
}
