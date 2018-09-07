// https://www.luogu.org/problemnew/show/P4248
// [AHOI2013]差异

#include <bits/stdc++.h>
using namespace std;

// Suffix array using radix sort
// which means the alphabet of the input string should be small
// END character must be the smallest
// See: 罗穗骞 后缀数组 - 处理字符串的有力工具
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

const int MAXN = 500010;
int64_t ans[MAXN];
int64_t ret;

int main() {
    string s;
    cin >> s;
    s += '`';
    SuffixArrayRadix sa(s);
    sa.buildSA();
    sa.buildLCP();
    stack<int> st;
    st.push(s.length()-1);
    for (int i = s.length()-2; i >= 1; i--) {
        while (sa.lcp[i] < sa.lcp[st.top()]) {
            st.pop();
        }
        ans[i] = 1LL * sa.lcp[i] * (st.top() - i) + ans[st.top()];
        st.push(i);
        ret -= 2*ans[i];
    }

    int n = s.length()-1;
    ret += (1LL*n*(n+1)*(2*n+1)/6 - 1LL*n*(n+1)/2)*3/2;
    printf("%ld\n", ret);

    return 0;
}
