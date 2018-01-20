// https://www.luogu.org/problemnew/show/3181
// [HAOI2016]找相同字符

#include <bits/stdc++.h>
using namespace std;


// Suffix array using radix sort
// which means the alphabet of the input string should be small
// END character must be the smallest
// MAXN must >= max(N, M)
const int MAXN = 400010;
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


int N1;
struct Item {
    int lcp, cnt[2];
} items[MAXN];
int front;
int64_t ps[MAXN][2];

int whichString(int pos) {
    return pos >= N1;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    s1 += ']';
    s2 += '[';
    N1 = s1.length();
    string s = s1 + s2;
    SuffixArrayRadix sa(s);
    sa.buildSA();
    sa.buildLCP();

    int64_t ans = 0;
    for (int i = 2; i < sa.N; i++) {
        int cnt[2];
        int from = whichString(sa.sa[i]);
        cnt[from] = 1; cnt[1-from] = 0;
        int64_t lcp = sa.lcp[i];
        while (front > 0 && items[front-1].lcp >= lcp) {
            ans += items[front-1].lcp * items[front-1].cnt[1-from];
            cnt[0] += items[front-1].cnt[0];
            cnt[1] += items[front-1].cnt[1];
            front--;
        }
        if (front > 0) {
            ans += ps[front-1][1-from];
        }
        items[front].lcp = lcp;
        items[front].cnt[0] = cnt[0];
        items[front].cnt[1] = cnt[1];
        for (int j = 0; j < 2; j++) {
            ps[front][j] = lcp * cnt[j];
            if (front > 0) ps[front][j] += ps[front-1][j];
        }
        front++;
    }

    printf("%lld\n", ans);
    return 0;
}
