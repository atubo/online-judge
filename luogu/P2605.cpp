// https://www.luogu.org/problemnew/show/P2605
// [ZJOI2010]基站选址

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int N;
    int64_t *mx, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        mx = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
    }

    ~SegmentTree() {
        delete[] mx;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 0, N-1, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, a, b, 0, N-1);
    }

    void reset() {
        memset(lazy, 0, 4*N*sizeof(int64_t));
        memset(mx, 0, 4*N*sizeof(int64_t));
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            mx[k] += t;
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        mx[k] = min(mx[2*k], mx[2*k+1]);
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        mx[2*k] += lazy[k];
        mx[2*k+1] += lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [L, R]
    int64_t query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        pushDown(k, L, R);
        if (a <= L && R <= b) return mx[k];
        int64_t ans = INT_MAX;
        int mid = (L + R) / 2;
        if (a <= mid) ans = min(ans, query(2*k, a, b, L, mid));
        if (mid < b)  ans = min(ans, query(2*k+1, a, b, mid+1, R));
        return ans;
    }
};

const int MAXN = 20010;
int N, K;
int D[MAXN], C[MAXN], S[MAXN], W[MAXN];
vector<vector<int>> last(MAXN);
struct Coverage {
    int left, right;
} coverage[MAXN];

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 2; i <= N; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &S[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &W[i]);
    }

    for (int i = 1; i <= N; i++) {
        int x = D[i] - S[i];
        int left = lower_bound(D+1, D+N+1, x) - D;
        x = D[i] + S[i];
        int *p = lower_bound(D+1, D+N+1, x);
        if (p == D+N+1 || *p > x) p--;
        int right = p - D;
        coverage[i] = {left, right};
        last[right].push_back(i);
    }

    vector<int64_t> f1(MAXN), f2(MAXN);
    for (int i = 1; i <= N; i++) f1[i] = INT_MAX;
    SegmentTree st(N+1);
    for (int k = 1; k <= K; k++) {
        st.reset();
        for (int i = 1; i <= N; i++) {
            int64_t q = st.query(0, i-1);
            f2[i] = q + C[i];
            for (int x: last[i]) {
                st.update(W[x], 0, coverage[x].left-1);
            }
            st.update(f1[i], i, i);
        }
        swap(f1, f2);
    }

    st.reset();
    for (int i = 1;i <= N; i++) {
        for (int x: last[i]) {
            st.update(W[x], 0, coverage[x].left-1);
        }
        st.update(f1[i], i, i);
    }
    printf("%lld", st.query(1, N));

    return 0;
}
