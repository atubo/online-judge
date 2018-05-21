// https://www.luogu.org/problemnew/show/P2824
// [HEOI2016/TJOI2016]排序

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int[4*N]{};
        lazy = new int[4*N]{};
        memset(lazy, -1, 4*N*sizeof(int));
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] = t * (r-l+1);
            lazy[k] = t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = val[2*k] + val[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (lazy[k] == -1 || l == r) return;
        lazy[2*k] = lazy[k];
        lazy[2*k+1] = lazy[k];
        int mid = (l + r) / 2;
        if (lazy[k]) {
            val[2*k] = mid - l + 1;
            val[2*k+1] = r - mid;
        } else {
            val[2*k] = val[2*k+1] = 0;
        }
        lazy[k] = -1;
    }

    // query range sum in [a, b], current node is [L, R]
    int query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        pushDown(k, L, R);
        if (a <= L && R <= b) return val[k];
        int sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += query(2*k, a, b, L, mid);
        if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
        return sum;
    }
};

const int MAXN = 100010;
int N, M, Q;
int A[MAXN];
struct Op {
    int type, left, right;
} op[MAXN];

bool feasible(int x) {
    SegmentTree st(N);
    for (int i = 1; i <= N; i++) {
        st.update((A[i] >= x), i, i);
    }
    for (int i = 0; i < M; i++) {
        int o = op[i].type;
        int l = op[i].left, r = op[i].right;
        int cnt = st.query(l, r);
        if (o == 0) {
            st.update(0, l, r-cnt);
            st.update(1, r-cnt+1, r);
        } else {
            st.update(1, l, l+cnt-1);
            st.update(0, l+cnt, r);
        }
    }

    int res = st.query(Q, Q);
    return res == 1;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < M; i++) {
        int o, l, r;
        scanf("%d%d%d", &o, &l, &r);
        op[i] = {o, l, r};
    }
    scanf("%d", &Q);

    int lo = 1, hi = N+1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid;
    }
    printf("%d\n", lo);
    return 0;
}
