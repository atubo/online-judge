// https://www.luogu.org/problemnew/show/P4094
// [HEOI2016/TJOI2016]字符串

#include <bits/stdc++.h>
using namespace std;

class SuffixArrayRadix {
public:
    SuffixArrayRadix(const string &s_):s(s_), N(s.length()) {
        char cmin = 0x7F, cmax = 0;
        for (char c: s) {
            cmin = min(cmin, c);
            cmax = max(cmax, c);
        }
        M = cmax - cmin + 1;
        MAXN = max(M, N);

        wa = new int[MAXN]{};
        wb = new int[MAXN]{};
        wv = new int[MAXN]{};
        ws = new int[MAXN]{};
        sa = new int[MAXN]{};
        r  = new int[MAXN]{};
        lcp = new int[MAXN]{};

        for (int i = 0; i < N; i++) {
            r[i] = s[i] - cmin;
        }

        nlog_ = int(log2(MAXN)) + 2;
        height_ = new int*[nlog_]{};
        for (int i = 0; i < nlog_; i++) {
            height_[i] = new int[MAXN]{};
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

        for (int i = 0; i < nlog_; i++) {
            delete[] height_[i];
        }
        delete[] height_;
    }
    int *wa, *wb, *wv, *ws;
    int *sa, *r, *rank;
    int *lcp;
    int **height_;
    int nlog_;

    void buildSA() {
        buildSA(N, M);
    }

    void buildLCP() {
        for (int i = 0, k = 0; i < N; ++i) if (rank[i] != N - 1) {
            for (int j = sa[rank[i] + 1]; s[i + k] == s[j + k];)
                ++k;
            lcp[rank[i]] = k;
            if (k)--k;
        }
    }

    void buildRMQ() {
        for (int i = 0; i < N; i++) {
            height_[0][i] = lcp[i];
        }
        for (int j = 1; (1<<j) < N; j++) {
            for (int i = 0; i < N; i++) {
                if (i + (1<<j) > N) break;
                height_[j][i] = min(height_[j-1][i],
                                    height_[j-1][i+(1<<(j-1))]);
            }
        }
    }

    int calcLCP(int x, int y) const {
        x = rank[x]; y = rank[y];
        if (x > y) swap(x, y);
        int k = 0;
        while ((1<<(k+1)) < (y-x)) k++;
        return min(height_[k][x], height_[k][y-(1<<k)]);
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
    int MAXN;
};

class PersistentSegmentTree {
public:
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int sum;

        Node(): L(0), R(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        T = new Node[(N+1) * int(log2(M)+2)]{};
    }

    ~PersistentSegmentTree() {
        delete[] root;
        delete[] T;
    }

    // for user's convenience
    void insert(int currRootIndex, int prevRootIndex, int x, int t) {
        root[currRootIndex] = root[prevRootIndex];
        insert(root[currRootIndex], x, t, 0, M-1);
    }

    // query in range [start, end]
    int query(int rootIndex, int start, int end) const {
        return query(root[rootIndex], start, end, 0, M-1);
    }

private:
    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].sum += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    int query(int node, int start, int end, int l, int r) const {
        if (l > r) return 0;
        if (start <= l && r <= end) return T[node].sum;
        int mid = (l + r) / 2;
        int ret = 0;
        if (start <= mid) ret += query(T[node].L, start, end, l, mid);
        if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
        return ret;
    }
};

class SegmentTreeSPU {
    static const int NULL_VALUE = INT_MAX;
public:
    SegmentTreeSPU(int n) {
        nData_ = 1;
        while (nData_ < n) nData_ = nData_ << 1;
        int sz = 2 * nData_ + 1;
        data = new int[sz];
        for (int i = 0; i < sz; i++) data[i] = NULL_VALUE;
    }

    ~SegmentTreeSPU() {
        delete[] data;
    }

    void update(int i, int value) {
        i += nData_;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    void build() {
        // assume all leaf nodes are already set up
        for (int i = nData_-1; i >= 1; i--) {
            data[i] = combine(data[2*i], data[2*i+1]);
        }
    }

    int query(int a, int b) const {
        a += nData_;
        b += nData_;
        int res = NULL_VALUE;
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 1) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

    int query() const {
        return data[1];
    }
public:
    int *data;
    int nData_;
    int combine(int a, int b) const {
        return min(a, b);
    }
};

int N, M;

int findLeft(const SegmentTreeSPU &st, int c, int th) {
    if (c == 0 || st.query(c-1, c-1) < th) return c;
    if (st.query(0, c-1) >= th) return 0;
    int lo = 0, hi = c-1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (st.query(mid, c-1) >= th) hi = mid;
        else lo = mid;
    }
    return hi;
}

int findRight(const SegmentTreeSPU &st, int c, int th) {
    if (c == N-1 || st.query(c, c) < th) return c-1;
    if (st.query(c, N-1) >= th) return N-1;
    int lo = c, hi = N-1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (st.query(c, mid) >= th) lo = mid;
        else hi = mid;
    }
    return lo;
}

bool check(const PersistentSegmentTree &pst,
           int a, int b, int len, int left, int right) {
    if (b < a + len - 1) return false;
    if (pst.query(b-len+2, left, right) - pst.query(a, left, right) == 0) {
        return false;
    }
    return true;
}

int solve(const SegmentTreeSPU &st, SuffixArrayRadix &sa,
          const PersistentSegmentTree &pst,
          int a, int b, int c, int d) {
    int hi = d - c + 2;
    int lo = 0;
    int rc = sa.rank[c];
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        int left = findLeft(st, rc, mid);
        int right = findRight(st, rc, mid);
        if (check(pst, a, b, mid, left, right+1)) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main() {
    scanf("%d%d", &N, &M);
    string s;
    cin >> s;
    s.push_back('`');
    N++;

    SuffixArrayRadix sa(s);
    sa.buildSA();
    sa.buildLCP();

    SegmentTreeSPU st(N);
    for (int i = 0; i < N; i++) {
        st.data[i+st.nData_] = sa.lcp[i];
    }
    st.build();

    PersistentSegmentTree pst(N, N);
    for (int i = 1; i <= N; i++) {
        pst.insert(i, i-1, sa.rank[i-1], 1);
    }

    for (int i = 0; i < M; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a--; b--; c--; d--;
        int ans = solve(st, sa, pst, a, b, c, d);
        printf("%d\n", ans);
    }

    return 0;
}
