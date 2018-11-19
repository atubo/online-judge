// https://www.luogu.org/problemnew/show/P2743
// [USACO5.1]乐曲主题Musical Themes

#include <bits/stdc++.h>
using namespace std;

class SuffixArrayRadix {
public:
    SuffixArrayRadix(const vector<int> &s_):s(s_), N(s.size()) {
        int cmin = 0xFF, cmax = 0;
        for (int c: s) {
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

    const vector<int> &s;
public:
    const int N;
private:
    int M;
    int MAXN;
};

class SparseTableRMQ {
public:
    int N, MAXB;
    const vector<int>& A;
    vector<vector<int> > stMin, stMax;

public:
    SparseTableRMQ(const vector<int> &a): N(a.size()), A(a) {
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
            MAXB++;
            x = x * 2;
        }

        stMin.resize(N);
        stMax.resize(N);
        for (int i = 0; i < N; i++) {
            stMin[i].resize(MAXB, INT_MAX);
            stMin[i][0] = A[i];
            stMax[i].resize(MAXB, INT_MIN);
            stMax[i][0] = A[i];
        }

        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                stMin[i][j] = min(stMin[i][j-1], stMin[i+(1<<(j-1))][j-1]);
                stMax[i][j] = max(stMax[i][j-1], stMax[i+(1<<(j-1))][j-1]);
            }
        }
    }

    int rmqMin(int u, int v) const {
        int j = 0;
        while (u + (1 << (j+1)) < v+1) j++;
        return min(stMin[u][j], stMin[v+1-(1<<j)][j]);
    }

    int rmqMax(int u, int v) const {
        int j = 0;
        while (u + (1 << (j+1)) < v+1) j++;
        return max(stMax[u][j], stMax[v+1-(1<<j)][j]);
    }
};
int N;

bool check(int l, const SuffixArrayRadix &sa, const SparseTableRMQ &rmq) {
    int p = 0;
    while (true) {
        while (p <= N && sa.lcp[p] < l) p++;
        if (p > N) return false;
        int q = p+1;
        while (q <= N && sa.lcp[q] >= l) q++;
        int x = rmq.rmqMin(p, q);
        int y = rmq.rmqMax(p, q);
        if (y - x >= l+1) return true;
        p = q;
    }
    return false;
}

int main() {
    scanf("%d", &N);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = N-1; i >= 1; i--) {
        A[i] = A[i] - A[i-1] + 88;
    }
    A[0] = 176;
    A.push_back(0);

    SuffixArrayRadix sa(A);
    sa.buildSA();
    sa.buildLCP();
    vector<int> s(N+1);
    for (int i = 0; i <= N; i++) {
        s[i] = sa.sa[i];
    }

    SparseTableRMQ rmq(s);
    rmq.preCompute();

    int lo = 4, hi = N/2+3;
    if (!check(lo, sa, rmq)) {
        printf("0");
        return 0;
    }
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid, sa, rmq)) lo = mid;
        else hi = mid;
    }
    printf("%d", lo+1);
    return 0;
}
