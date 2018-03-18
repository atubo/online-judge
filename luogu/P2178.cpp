// https://www.luogu.org/problemnew/show/P2178
// [NOI2015]品酒大会

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300010;
class SuffixArrayRadix {
public:
    SuffixArrayRadix(const string &s_):s(s_), N(s.length()) {
        wa = new int[MAXN];
        wb = new int[MAXN];
        wv = new int[MAXN];
        ws = new int[MAXN];
        sa = new int[MAXN];
        r  = new int[MAXN];
        lcp = new int[MAXN];

        char cmin = 0x7F, cmax = 0;
        for (char c: s) {
            cmin = min(cmin, c);
            cmax = max(cmax, c);
        }
        M = cmax - cmin + 1;
        for (int i = 0; i < N; i++) {
            r[i] = s[i] - cmin;
        }
    }

    ~SuffixArrayRadix() {
        delete[] wa;
        delete[] wb;
        delete[] wv;
        delete[] ws;
        delete[] sa;
        delete[] r;
        delete[] lcp;
    }
    int *wa, *wb, *wv, *ws;
    int *sa, *r, *rank;
    int *lcp;

    void buildSA() {
        buildSA(N, M);
    }

    void buildLCP() {
        for (int i = 0, k = 0; i < N; ++i) if (rank[i] != N - 1)
        {
            for (int j = sa[rank[i] + 1]; s[i + k] == s[j + k];)
                ++k;
            lcp[rank[i]] = k;
            if (k)--k;
        }
    }

private:
    int cmp(int *arr, int a, int b, int l) {
        return arr[a] == arr[b] && arr[a+l] == arr[b+l];
    }

    void buildSA(int n, int m) {
        int i, j, p, *x = wa, *y = wb, *t;
        // first round of radix sort
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < n; i++) ws[x[i]=r[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i-1];
        for (i = n-1; i >= 0; i--) sa[--ws[x[i]]] = i;
        for (j=1, p=1; p < n; j*=2,m=p) {
            // sort by the second key
            for (p=0, i=n-j; i<n; i++) y[p++] = i;
            for (i=0; i<n; i++) if (sa[i]>=j) y[p++] = sa[i]-j;
            // sort by the first key
            for (i=0; i<n; i++) wv[i] = x[y[i]];
            for (i=0; i<m; i++) ws[i] = 0;
            for (i=0; i<n; i++) ws[wv[i]]++;
            for (i=1; i<m; i++) ws[i] += ws[i-1];
            for (i=n-1; i>=0; i--) sa[--ws[wv[i]]] = y[i];
            for (t=x, x=y, y=t, p=1, x[sa[0]]=0, i=1; i<n; i++) {
                x[sa[i]]=cmp(y, sa[i-1], sa[i], j)?p-1:p++;
            }
        }
        rank = x;
    }

    const string &s;
public:
    const int N;
private:
    int M;
};

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

using Pii = pair<int, int>;

class SegmentTreeMin {
public:
    SegmentTreeMin(int n):data(max(3*n, 30)), nData(n) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = make_pair(value, i - nData - 1);
        for (; i > 1; i >>= 1) {
            auto newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    Pii query(int a, int b) const {
        a += nData + 1;
        b += nData + 1;
        auto res = data[a];
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

    Pii query() const {
        return data[1];
    }
private:
    vector<Pii> data;
    int nData;
    Pii combine(const Pii &a, const Pii &b) const {
        if (a.first < b.first) return a;
        else return b;
    }
};

class SegmentTreeMax {
public:
    SegmentTreeMax(int n) :data(max(3*n, 30)), nData(n) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = make_pair(value, i - nData - 1);
        for (; i > 1; i >>= 1) {
            auto newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    Pii query(int a, int b) const {
        a += nData + 1;
        b += nData + 1;
        auto res = data[a];
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

    Pii query() const {
        return data[1];
    }
private:
    vector<Pii> data;
    int nData;
    Pii combine(const Pii &a, const Pii &b) const {
        if (a.first > b.first) return a;
        return b;
    }
};

int N;
int A[MAXN];
int64_t B[MAXN], C[MAXN];

Pii getUpper(SegmentTreeMax &st, int p, int q) {
    Pii p1 = st.query(p, q);
    st.update(p1.second, -1);
    Pii p2 = st.query(p, q);
    Pii res = make_pair(p1.first, p2.first);
    st.update(p1.second, p1.first);
    return res;
}

Pii getLower(SegmentTreeMin &st, int p, int q) {
    Pii p1 = st.query(p, q);
    st.update(p1.second, 0);
    Pii p2 = st.query(p, q);
    Pii res = make_pair(p1.first, p2.first);
    st.update(p1.second, p1.first);
    return res;
}

Pii getMid(const SegmentTreeMin &st2,
           const SegmentTreeMax &st3,
           int p, int q) {
    Pii p1 = st2.query(p, q);
    Pii p2 = st3.query(p, q);
    return make_pair(p1.first, p2.first);
}


int64_t solve(SegmentTreeMax &st1,
              const SegmentTreeMin &st2,
              const SegmentTreeMax &st3,
              SegmentTreeMin &st4,
              int p, int q) {
    assert(p < q);
    const auto upper = getUpper(st1, p, q);
    const auto lower = getLower(st4, p, q);
    int64_t res = -4e18;
    if (upper.first >= 0 && upper.second >= 0) {
        res = max(res, int64_t(upper.first) * upper.second);
    }
    if (lower.first < 0 && lower.second < 0) {
        res = max(res, int64_t(lower.first) * lower.second);
    }
    if (res < 0) {
        const auto mid = getMid(st2, st3, p, q);
        res = int64_t(mid.first) * mid.second;
    }
    return res;
}

int main() {
    scanf("%d", &N);
    string s;
    cin >> s;
    s.push_back('`');
    SuffixArrayRadix sa(s);
    sa.buildSA();
    sa.buildLCP();

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    SegmentTreeMax stmaxpos(N), stmaxneg(N);
    SegmentTreeMin stminpos(N), stminneg(N);

    for (int i = 1; i <= N; i++) {
        int x = A[sa.sa[i]];
        if (x >= 0) {
            stmaxpos.update(i, x);
            stminpos.update(i, x);
            stmaxneg.update(i, INT_MIN);
            stminneg.update(i, 0);
        } else {
            stmaxpos.update(i, -1);
            stminpos.update(i, INT_MAX);
            stmaxneg.update(i, x);
            stminneg.update(i, x);
        }
        B[i] = -4e18;
    }

    SegmentTree st(N);
    stack<pair<int, int>> q;
    q.push(make_pair(0, 0));
    for (int i = 1; i < N; i++) {
        int h = sa.lcp[i];
        while (!q.empty() && q.top().first > h) {
            int h2 = q.top().first;
            int j  = q.top().second;
            q.pop();
            int h3 = h + 1;
            if (!q.empty()) {
                h3 = max(h3, q.top().first + 1);
                j  = q.top().second + 1;
            }
            int64_t v = int64_t(i-j) * (i-j+1) / 2;
            st.update(v, h3+1, h2+1);
            B[h2] = max(B[h2],
                        solve(stmaxpos, stminpos, stmaxneg, stminneg, j, i));
        }
        if (q.empty() || h > q.top().first) {
            q.push(make_pair(h, i));
        } else {
            q.top().second = i;
        }
    }

    while (q.top().first > 0) {
        int h = q.top().first;
        int j = q.top().second;
        q.pop();
        if (!q.empty()) j = q.top().second + 1;
        int64_t v = int64_t(N-j) * (N-j+1) / 2;
        int prev = (q.empty() ? 0 : q.top().first+1);
        st.update(v, prev+1, h+1);
        B[h] = max(B[h],
                   solve(stmaxpos, stminpos, stmaxneg, stminneg, j, N));
    }
    int64_t v = int64_t(N) * (N-1) / 2;
    st.update(v, 1, 1);
    B[0] = solve(stmaxpos, stminpos, stmaxneg, stminneg, 1, N);
    for (int i = 0; i < N; i++) {
        C[i] = st.query(i+1, i+1);
    }

    for (int i = N-1; i >= 0; i--) {
        if (C[i] == 0) B[i] = -4e18;
        else B[i] = max(B[i], B[i+1]);
    }
    for (int i = 0; i < N; i++) {
        if (C[i] == 0) B[i] = 0;
        printf("%lld %lld\n", C[i], B[i]);
    }

    return 0;
}
