// https://www.luogu.org/problemnew/show/P1117
// [NOI2016]优秀的拆分

#include <bits/stdc++.h>
using namespace std;

/*
Suffix array O(n lg^2 n)
LCP table O(n)
*/
// see http://web.stanford.edu/class/cs97si/suffix-array.pdf

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

// lcp(i) = LCP(i, i+1)
namespace SuffixArray
{
    const int MAXN = 1 << 21;
    const int MAXP = 22;
    const char * S;
    int N, gap;
    int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];
    int P[MAXP][MAXN];
    int height[MAXP][MAXN];
    int NP;

    bool sufCmp(int i, int j)
    {
        if (pos[i] != pos[j])
            return pos[i] < pos[j];
        i += gap;
        j += gap;
        return (i < N && j < N) ? pos[i] < pos[j] : i > j;
    }

    void buildSA()
    {
        N = strlen(S);
        REP(i, N) sa[i] = i, pos[i] = S[i];
        gap = 0;
        sort(sa, sa + N, sufCmp);
        REP(i, N-1) tmp[i+1] = tmp[i] + sufCmp(sa[i], sa[i+1]);
        REP(i, N) P[0][sa[i]] = tmp[i];
        for (NP = 1, gap = 1; gap >> 1 < N; gap *= 2)
        {
            sort(sa, sa + N, sufCmp);
            REP(i, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
            REP(i, N) pos[sa[i]] = tmp[i];
            REP(i, N) P[NP][sa[i]] = tmp[i];
            NP++;
            //if (tmp[N - 1] == N - 1) break;
        }
    }

    void buildLCP()
    {
        for (int i = 0, k = 0; i < N; ++i) if (pos[i] != N - 1)
        {
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
                ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
    }

    void buildRMQ() {
        for (int i = 0; i < N; i++) {
            height[0][i] = lcp[i];
        }
        for (int j = 1; (1<<j) < N; j++) {
            for (int i = 0; i < N; i++) {
                if (i + (1<<j) > N) break;
                height[j][i] = min(height[j-1][i], height[j-1][i+(1<<(j-1))]);
            }
        }
    }

    int calcLCP(int x, int y) {
        x = pos[x]; y = pos[y];
        if (x > y) swap(x, y);
        int k = 0;
        while ((1<<(k+1)) < (y-x)) k++;
        return min(height[k][x], height[k][y-(1<<k)]);
    }
} // end namespace SuffixArray

/* usage example
    SuffixArray::S = s.c_str();
    SuffixArray::buildSA();
    SuffixArray::buildLCP();
*/

class BIT {
public:
    // Note size needs to be power of 2
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }
    
    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // get largest value with cumulative sum less than or equal to x;
    // for smallest, pass x-1 and add 1 to result
    int getind(int x) {
        int idx = 0, mask = N;
        while(mask && idx < N) {
            int t = idx + mask;
            if(x >= tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx;
    }

private:
    int64_t* tree;
    const int N;
};

void solve(const string &s, BIT &ft1, BIT &ft2) {
    SuffixArray::S = s.c_str();
    SuffixArray::buildSA();
    SuffixArray::buildLCP();
    SuffixArray::buildRMQ();
    const int N = s.length()/2;
    for (int L = 1; L <= N/2; L++) {
        for (int a = 0; a + L < N; a += L) {
            int b = a + L;
            int suf = SuffixArray::calcLCP(a, b);
            int pre = SuffixArray::calcLCP(2*N-a, 2*N-b);
            if (suf + pre >= L + 1) {
                int start1 = max(a-L+1, a-pre+1);
                int start2 = min(a, a+suf-L);
                ft1.set(start1+1, 1);
                ft1.set(start2+2, -1);
                int end1 = max(b, b-pre+L);
                int end2 = min(b+suf-1, b+L-1);
                ft2.set(end1+1, 1);
                ft2.set(end2+2, -1);
            }
        }
    }
    int64_t res = 0;
    for (int i = 0; i < N-1; i++) {
        int64_t a = ft2.get(i+1);
        int64_t b = ft1.get(i+2);
        res += a * b;
    }
    printf("%lld\n", res);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        string S;
        cin >> S;
        string tmp = S;
        reverse(tmp.begin(), tmp.end());
        S.push_back('$');
        S += tmp;
        BIT ft1(S.length()+ 100), ft2(S.length() + 100);
        solve(S, ft1, ft2);
    }

    return 0;
}
