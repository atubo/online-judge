// https://www.luogu.org/problemnew/show/P3332
// [ZJOI2013]K大数查询

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010 * 2;

int64_t val[131100], lazy[131100];

class SegmentTree {
    int N;
    //vector<int64_t> val, lazy;

public:
    SegmentTree(int N_): N(N_) {}
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] += t * (r-l+1);
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = val[2*k] + val[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        int mid = (l + r) / 2;
        val[2*k] += (mid - l + 1) * lazy[k];
        val[2*k+1] += (r - mid) * lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [L, R]
    int64_t query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        pushDown(k, L, R);
        if (a <= L && R <= b) return val[k];
        int64_t sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += query(2*k, a, b, L, mid);
        if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
        return sum;
    }
};


const int MAXM = 50010;
int N, M, MAXC;
struct Query {int t, a, b, d, id; int64_t c;} Q[MAXM], tmpq[MAXM];
int64_t numset[MAXM];
int A[MAXM];

SegmentTree st(65536);

void process(int lo, int hi, int l, int r) {
    if (lo > hi) return;
    if (lo == hi) {
        for (int i = l; i <= r; i++) {
            if (Q[i].t == 1) {
                assert(Q[i].c == lo);
                st.update(1, Q[i].a, Q[i].b);
            } else {
                int64_t cnt = st.query(Q[i].a, Q[i].b);
                if (Q[i].c > cnt) Q[i].d = -1;
                else Q[i].d = lo;
            }
        }
        for (int i = l; i <= r; i++) {
            if (Q[i].t == 1) {
                assert(Q[i].c == lo);
                st.update(-1, Q[i].a, Q[i].b);
            }
        }
        return;
    }

    int mid = (lo + hi) / 2 + 1;
    int q = l;
    for (int i = l; i <= r; i++) {
        if (Q[i].t == 1) {
            if (Q[i].c >= mid) {
                st.update(1, Q[i].a, Q[i].b);
                Q[i].d = 1;
            } else {
                Q[i].d = 0;
                q++;
            }
        } else {
            int64_t cnt = st.query(Q[i].a, Q[i].b);
            if (cnt >= Q[i].c) {
                Q[i].d = 1;
            } else {
                Q[i].c -= cnt;
                Q[i].d = 0;
                q++;
            }
        }
    }
    for (int i = l; i <= r; i++) {
        if (Q[i].t == 1) {
            if (Q[i].c >= mid) {
                st.update(-1, Q[i].a, Q[i].b);
            }
        }
    }

    int u = q;
    int p = l;
    for (int i = l; i <= r; i++) {
        if (Q[i].d == 0) tmpq[p++] = Q[i];
        else             tmpq[q++] = Q[i];
    }

    for (int i = l; i <= r; i++) {
        Q[i] = tmpq[i];
    }
    process(lo, mid-1, l, u-1);
    process(mid, hi, u, r);
}

int main() {
    scanf("%d%d", &N, &M);
    int numt1 = 0;
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d%lld", &Q[i].t, &Q[i].a, &Q[i].b, &Q[i].c);
        Q[i].id = i;
        if (Q[i].t == 1) numset[numt1++] = Q[i].c;
    }
    sort(numset, numset+numt1);
    int64_t *end = unique(numset, numset+numt1);
    MAXC = max(1, int(end - numset));
    for (int i = 0; i < M; i++) {
        if (Q[i].t == 1) {
            Q[i].c = lower_bound(numset, end, Q[i].c) - numset + 1;
        }
    }
    process(1, MAXC, 0, M);
    for (int i = 0; i < M; i++) A[i] = -2;
    for (int i = 0; i < M; i++) {
        if (Q[i].t == 2) {
            int ret = (Q[i].d == -1 ? -1 : numset[Q[i].d-1]);
            A[Q[i].id] = ret;
        }
    }
    for (int i = 0; i < M; i++) {
        if (A[i] > -2) printf("%d\n", A[i]);
    }
    return 0;
}
