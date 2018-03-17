// https://www.luogu.org/problemnew/show/P2178
// [NOI2015]品酒大会

#include <bits/stdc++.h>
using namespace std;

// Suffix array using radix sort
// which means the alphabet of the input string should be small
// END character must be the smallest
// MAXN must >= max(N, M)
// See: 罗穗骞 后缀数组 - 处理字符串的有力工具
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

int N;
int A[MAXN];

int main() {
    scanf("%d", &N);
    string s;
    cin >> s;
    s.push_back('`');
    SuffixArrayRadix sa(s);
    sa.buildSA();
    sa.buildLCP();

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
        int64_t v = int64_t(N-j) * (N-j+1) / 2;
        int prev = (q.empty() ? 0 : q.top().first+1);
        st.update(v, prev+1, h+1);
    }
    int64_t v = int64_t(N) * (N-1) / 2;
    st.update(v, 1, 1);
    for (int i = 0; i < N; i++) {
        printf("%lld\n", st.query(i+1, i+1));
    }

    return 0;
}
