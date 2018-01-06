// https://www.luogu.org/problemnew/show/P2852
// [USACO06DEC]牛奶模式Milk Patterns

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
    int S[MAXN];
    int N, gap;
    int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];
    int P[MAXP][MAXN];
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

    int calcLCP(int x, int y)
    {
        int k, ret = 0;
        if (x == y) return N-x;
        for (k = NP-1; k >= 0 && x < N && y < N; k--) {
            if (P[k][x] == P[k][y]) {
                x += 1 << k;
                y += 1 << k;
                ret += 1 << k;
            }
        }
        return ret;
    }
} // end namespace SuffixArray

/* usage example
    SuffixArray::S = s.c_str();
    SuffixArray::buildSA();
    SuffixArray::buildLCP();
*/

int main() {
    using namespace SuffixArray;
    using PII = pair<int, int>;
    int K;
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    buildSA();
    buildLCP();

#if 0
    for (int i = 0; i < N; i++) {
        printf("%d ", sa[i]);
    }
    printf("\n");
    for (int i = 0; i < N-1; i++) {
        printf("%d ", lcp[i]);
    }
    printf("\n");
#endif

    int ans = 0;
    deque<PII> dq;
    for (int i = 1; i < N; i++) {
        int p = i-1;
        int x = lcp[p];
        while (!dq.empty() && dq.back().second > x) {
            p = dq.back().first;
            dq.pop_back();
        }
        dq.push_back(make_pair(p, x));
        while (!dq.empty() && dq.front().first <= (i-K+1)) {
            ans = max(ans, dq.front().second);
            dq.pop_front();
        }
    }
    printf("%d\n", ans);

    return 0;
}
