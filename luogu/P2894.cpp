// https://www.luogu.org/problemnew/show/P2894
// [USACO08FEB]酒店Hotel

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int *left, *right, *middle, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        left = new int[4*N]{};
        right = new int[4*N]{};
        middle = new int[4*N]{};
        lazy = new int[4*N]{};
    }

    ~SegmentTree() {
        delete[] left;
        delete[] right;
        delete[] middle;
        delete[] lazy;
    }
    // put t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    int query(int t) {
        return query(1, t, 1, N);
    }

private:
    // put t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            left[k] = right[k] = middle[k] = (t == 1 ? 0 : r - l + 1);
            lazy[k] = t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        merge(k, l, r);
    }

    void merge(int k, int l, int r) {
        int mid = (l + r) / 2;
        left[k] = left[2*k] + (left[2*k] == mid - l + 1 ? left[2*k+1] : 0);
        right[k] = right[2*k+1] +
            (right[2*k+1] == r - mid ? right[2*k] : 0);
        middle[k] = max(middle[2*k], middle[2*k+1]);
        middle[k] = max(middle[k], right[2*k] + left[2*k+1]);
    }

    void pushDown(int k, int l, int r) {
        if (lazy[k] == -1 || l == r) return;
        lazy[2*k] = lazy[k];
        lazy[2*k+1] = lazy[k];
        int mid = (l + r) / 2;
        left[2*k] = right[2*k] = middle[2*k] =
            (lazy[k] == 1 ? 0 : mid - l + 1);
        left[2*k+1] = right[2*k+1] = middle[2*k+1] =
            (lazy[k] == 1 ? 0 : r - mid);
        lazy[k] = -1;
    }

    int query(int k, int t, int l, int r) {
        if (middle[k] < t) return 0;
        pushDown(k, l, r);
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (middle[2*k] >= t) return query(2*k, t, l, mid);
        int x = right[2*k];
        if (left[2*k+1] >= t-x) return mid - x + 1;
        else return query(2*k+1, t, mid+1, r);
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    SegmentTree st(N);
    st.update(0, 1, N);
    for (int i = 0; i < M; i++) {
        int t, x, y;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d", &x);
            int pos = st.query(x);
            printf("%d\n", pos);
            if (pos > 0) st.update(1, pos, pos+x-1);
        } else {
            scanf("%d%d", &x, &y);
            st.update(0, x, x+y-1);
        }
    }

    return 0;
}
