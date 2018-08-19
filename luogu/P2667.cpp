// https://www.luogu.org/problemnew/show/P2667
// [TJOI2012]防御

#include <bits/stdc++.h>
using namespace std;

// support query for range min
// note it's 1-indexed
class SegmentTreeMin {
    const int64_t MAXVAL = 1e12;
    int N;
    int64_t *val, *lazy;
    int *pos_;

public:
    struct QueryResult {
        int64_t value;
        int pos;
        bool operator < (const QueryResult &other) const {
            return value < other.value ||
                (value == other.value && pos < other.pos);
        }
    };

    const QueryResult NULL_RESULT{MAXVAL, -1};

    SegmentTreeMin(int N_): N(N_) {
        val = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
        pos_ = new int[4*N]{};

        setupPosition(1, 1, N);
    }

    ~SegmentTreeMin() {
        delete[] val;
        delete[] lazy;
        delete[] pos_;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    QueryResult query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    // initialize pos_
    void setupPosition(int k, int l, int r) {
        if (l == r) {
            pos_[k] = l;
            return;
        }

        int mid = (l + r) / 2;
        setupPosition(2*k, l, mid);
        setupPosition(2*k+1, mid+1, r);
        // assume initial values are the same
        pos_[k] = pos_[2*k];
    }

    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] += t;
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        int p = (val[2*k] <= val[2*k+1] ? 2*k : 2*k+1);
        val[k] = val[p];
        pos_[k] = pos_[p];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        val[2*k] += lazy[k];
        val[2*k+1] += lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [L, R]
    QueryResult query(int k, int a, int b, int L, int R) {
        auto ret = NULL_RESULT;
        if (!k) return ret;
        if (b < L || a > R) return ret;
        pushDown(k, L, R);
        if (a <= L && R <= b) {
            return QueryResult{val[k], pos_[k]};
        }
        int mid = (L + R) / 2;
        if (a <= mid) ret = min(ret, query(2*k, a, b, L, mid));
        if (mid < b)  ret = min(ret, query(2*k+1, a, b, mid+1, R));
        return ret;
    }
};

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(int64_t t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int64_t t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] += t * int64_t(r-l+1);
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
        val[2*k] += lazy[k] * int64_t(mid - l + 1);
        val[2*k+1] += lazy[k] * int64_t(r - mid);
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

const int MAXN = 100010;
const int MOD = 1000000009;
int N, Q;
int P[MAXN], residual[MAXN];
bool broken[MAXN];
int64_t ans;

int main() {
    scanf("%d%d", &N, &Q);
    SegmentTreeMin shield(N);
    SegmentTree damage(N);
    damage.update(-INT_MAX, 1, N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
        shield.update(P[i], i, i);
    }
    char cmd[10];
    for (int i = 0; i < Q; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'A') {
            int l, r, a;
            scanf("%d%d%d", &l, &r, &a);
            damage.update(2*a, l, r);

            shield.update(-a, l, r);
            while (true) {
                auto qr = shield.query(l, r);
                if (qr.value > 0) break;
                //printf("shield %d broken! value=%ld\n", qr.pos, qr.value);
                shield.update(INT_MAX, qr.pos, qr.pos);
                broken[qr.pos] = true;
                residual[qr.pos] = -qr.value;
                int d = - damage.query(qr.pos, qr.pos);
                damage.update(d, qr.pos, qr.pos);
            }
        } else {
            int x;
            scanf("%d", &x);
            int64_t t = 0;
            if (broken[x]) {
                t = P[x] + residual[x];
                (t += damage.query(x, x)) %= MOD;
            } else {
                t = int64_t(P[x]) - shield.query(x, x).value;
            }
            //printf("t=%ld\n", t);
            (ans += t) %= MOD;
        }
    }
    printf("%ld", ans);

    return 0;
}
