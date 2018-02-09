// https://www.luogu.org/problemnew/show/P1970
// 花匠

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int N;
    int *val;

public:
    SegmentTree(int N_): N(N_) {
        val = new int[4*(N+1)]{};
    }

    ~SegmentTree() {
        delete[] val;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range in [a, b]
    int query(int a, int b) {
        if (a > b) return 0;
        return query(1, a, b, 1, N);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] = t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = max(val[2*k], val[2*k+1]);
    }

    void pushDown(int k, int l, int r) {
    }

    // query range in [a, b], current node is [L, R]
    int query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        pushDown(k, L, R);
        if (a <= L && R <= b) return val[k];
        int ret = 0;
        int mid = (L + R) / 2;
        if (a <= mid) ret = max(ret, query(2*k, a, b, L, mid));
        if (mid < b)  ret = max(ret, query(2*k+1, a, b, mid+1, R));
        return ret;
    }
};


const int MAXN = 100010;
int N;
int H[MAXN];
int sorted[MAXN];
int *endp;

int idx(int x) {
    return lower_bound(sorted, endp, x) - sorted + 1;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
    }
    memcpy(sorted, H, N*sizeof(int));
    sort(sorted, sorted+N);
    endp = unique(sorted, sorted+N);

    int ret = 0;
    SegmentTree up(N), down(N);
    for (int i = 0; i < N; i++) {
        int x = idx(H[i]);
        int downlen = up.query(x+1, N) + 1;
        int uplen = down.query(1, x-1) + 1;
        down.update(downlen, x, x);
        up.update(uplen, x, x);
        ret = max(ret, max(downlen, uplen));
    }

    printf("%d\n", ret);

    return 0;
}
