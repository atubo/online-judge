// https://www.luogu.org/problemnew/show/P3071
// [USACO13JAN]座位Seating

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val, *lazy;
    int *left, *right, *middle;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
        left = new int[4*N]{};
        right = new int[4*N]{};
        middle = new int[4*N]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
        delete[] left;
        delete[] right;
        delete[] middle;
    }

    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    int query(int d) {
        return query(1, 1, N, d);
    }

private:
    void update(int k, int t, int l, int r, int a, int b) {
        assert(abs(t) == 1);
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            left[k] = right[k] = middle[k] = (t == 1 ? 0 : (r-l+1));
            lazy[k] = t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        left[k] = left[2*k];
        if (left[k] == mid-l+1) left[k] += left[2*k+1];
        right[k] = right[2*k+1];
        if (right[k] == r-mid) right[k] += right[2*k];
        middle[k] = max(middle[2*k], middle[2*k+1]);
        middle[k] = max(middle[k], right[2*k]+left[2*k+1]);
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] = lazy[k];
        lazy[2*k+1] = lazy[k];
        int mid = (l + r) / 2;
        left[2*k] = right[2*k] = middle[2*k] =
            (lazy[k] == 1 ? 0 : mid-l+1);
        left[2*k+1] = right[2*k+1] = middle[2*k+1] =
            (lazy[k] == 1 ? 0 : r-mid);
        lazy[k] = 0;
    }

    int query(int k, int L, int R, int d) {
        if (middle[k] < d) return -1;
        if (left[k] >= d) return L;
        int mid = (L + R) / 2;
        if (middle[2*k] >= d) return query(2*k, L, mid, d);
        int ans = -1;
        if (right[2*k]+left[2*k+1] >= d) {
            ans = mid-right[2*k]+1;
        } else {
            ans = query(2*k+1, mid+1, R, d);
        }
        return ans;
    }


};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    SegmentTree st(N);
    st.update(-1, 1, N);
    char cmd[10];
    int x, y;
    int ans = 0;
    for (int i = 0; i < M; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'A') {
            scanf("%d", &x);
            int p = st.query(x);
            //printf("%d\n", p);
            if (p > -1) st.update(1, p, p+x-1);
            else ans++;
        } else {
            scanf("%d%d", &x, &y);
            st.update(-1, x, y);
        }
    }
    printf("%d\n", ans);
    return 0;
}
