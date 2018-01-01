// https://www.luogu.org/problemnew/show/P3332
// [ZJOI2013]K大数查询

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010 * 16 * 16 * 1.5;

int64_t val[MAXN];
int lc[MAXN], rc[MAXN];
int lazy[MAXN];
int root[50010*2];

// outer is weight, inner is position
struct SegTreeInSegTree {
    // both n and tn starts from 1
    int n;  // number of positions
    int tn; // number of weights
    int innerCnt;
    //vector<int> root;

    SegTreeInSegTree(int n_, int tn_):
        n(n_), tn(tn_), innerCnt(1) {}

    // add value t to weight node w at range[a, b]
    void update(int a, int b, int w, int t) {
        int k = 1, l = 1, r = tn;
        while (l != r) {
            int mid = (l + r) / 2;
            updateInner(root[k], t, 1, n, a, b);
            if (w <= mid) {
                r = mid;
                k = 2*k;
            } else {
                l = mid+1;
                k = 2*k + 1;
            }
        }
        updateInner(root[k], t, 1, n, a, b);
    }

    // weight sum in range [l, r] for position [a, b]
    // current node is [L, R]
    int64_t query(int k, int a, int b, int l, int r, int L, int R) {
        if (l > r || a > b) return 0;
        if (l > R || r < L) return 0;
        if (l <= L && R <= r) {
            return queryInner(root[k], a, b, 1, n);
        }
        int64_t sum = 0;
        int mid = (L + R) / 2;
        if (l <= mid) sum += query(2*k, a, b, l, r, L, mid);
        if (mid < r)  sum += query(2*k+1, a, b, l, r, mid+1, R);
        return sum;
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void updateInner(int &now, int t, int l, int r, int a, int b) {
        if (a > b) return;
        if (!now) now = innerCnt++;
        pushDown(now, l, r);
        if (a <= l && r <= b) {
            val[now] += t * (r-l+1);
            lazy[now] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) updateInner(lc[now], t, l, mid, a, b);
        if (mid < b)  updateInner(rc[now], t, mid+1, r, a, b);
        val[now] = val[lc[now]] + val[rc[now]];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        if (!lc[k]) lc[k] = innerCnt++;
        if (!rc[k]) rc[k] = innerCnt++;
        lazy[lc[k]] += lazy[k];
        lazy[rc[k]] += lazy[k];
        int mid = (l + r) / 2;
        val[lc[k]] += (mid - l + 1) * lazy[k];
        val[rc[k]] += (r - mid) * lazy[k];
        lazy[k] = 0;
    }

    // query weight sum in position range [a, b]
    // current node is [L, R]
    int64_t queryInner(int node, int a, int b, int L, int R) {
        if (!node) return 0;
        if (b < L || a > R) return 0;
        pushDown(node, L, R);
        if (a <= L && R <= b) return val[node];
        int64_t sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += queryInner(lc[node], a, b, L, mid);
        if (mid < b)  sum += queryInner(rc[node], a, b, mid+1, R);
        return sum;
    }
};

const int MAXM = 50010;
int N, M, MAXC;
struct Query {int t, a, b; int64_t c;} Q[MAXM];
int64_t numset[MAXM];

void update(SegTreeInSegTree &st, int a, int b, int c) {
    st.update(a, b, c, 1);
}

int query(SegTreeInSegTree &st, int a, int b, int64_t c) {
    const int64_t NW = st.query(1, a, b, 1, MAXC, 1, MAXC);
    if (c <= 0 || NW < c) return -1;
    c = NW - c + 1;
    int k = 1, l = 1, r = MAXC;
    while (l < r) {
        int mid = (l + r) / 2;
        int64_t cntLeft = st.query(2*k, a, b, l, mid, l, mid);
        if (cntLeft >= c) {
            k *= 2;
            r = mid;
        } else {
            k = 2*k + 1;
            l = mid + 1;
            c -= cntLeft;
        }
    }
    return l;
}

int main() {
    scanf("%d%d", &N, &M);
    int numt1 = 0;
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d%lld", &Q[i].t, &Q[i].a, &Q[i].b, &Q[i].c);
        if (Q[i].t == 1) numset[numt1++] = Q[i].c;
    }
    sort(numset, numset+numt1);
    int64_t *end = unique(numset, numset+numt1);
    MAXC = end - numset;
    for (int i = 0; i < M; i++) {
        if (Q[i].t == 1) {
            Q[i].c = lower_bound(numset, end, Q[i].c) - numset + 1;
        }
    }
    SegTreeInSegTree st(N, MAXC);
    for (int i = 0; i < M; i++) {
        if (Q[i].t == 1) update(st, Q[i].a, Q[i].b, Q[i].c);
        else {
            int idx = query(st, Q[i].a, Q[i].b, Q[i].c);
            int64_t ret = (idx == -1 ? -1 : numset[idx-1]);
            printf("%lld\n", ret);
        }
    }
    return 0;
}
