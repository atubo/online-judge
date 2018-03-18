// https://www.luogu.org/problemnew/show/P2463
// [SDOI2008]Sandy的卡片

#include <bits/stdc++.h>
using namespace std;


#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

// lcp(i) = LCP(i, i+1)
namespace SuffixArray
{
    const int MAXN = 1 << 21;
    const int MAXP = 22;
    const int * S;
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
        //N = strlen(S);
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

const int MAXN = 1000010;
int N;
int cnt[MAXN];

struct Counter {
    Counter(): sz(0) {}
    int sz;
    void inc(int x) {
        if (cnt[x]++ == 0) sz++;
    }
    void dec(int x) {
        if (--cnt[x] == 0) sz--;
    }

    int count() const {
        return sz;
    }
};

int main() {
    scanf("%d", &N);
    vector<int> C(N);
    vector<int> A;
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
        int prev;
        scanf("%d", &prev);
        for (int j = 1; j < C[i]; j++) {
            int x;
            scanf("%d", &x);
            A.push_back(x - prev);
            prev = x;
        }
        A.push_back(INT_MAX-i);
    }
    SuffixArray::S = &A[0];
    SuffixArray::N = A.size();
    SuffixArray::buildSA();
    SuffixArray::buildLCP();

    for (int i = 1; i < N; i++) {
        C[i] += C[i-1];
    }

    vector<int> G(A.size());
    for (int i = 0; i < (int)G.size(); i++) {
        G[i] = upper_bound(C.begin(), C.end(), SuffixArray::sa[i]) - C.begin();
    }

    int res = 0;
    Counter groups;
    multiset<int> lcps;
    int p = 0;
    lcps.insert(SuffixArray::lcp[p]);
    groups.inc(G[p]);
    for (int q = 1; q < SuffixArray::N; q++) {
        groups.inc(G[q]);
        while (groups.count() == N) {
            res = max(res, *lcps.begin());
            groups.dec(G[p]);
            lcps.erase(lcps.find(SuffixArray::lcp[p]));
            p++;
        }
        lcps.insert(SuffixArray::lcp[q]);
    }

    printf("%d\n", res+1);

    return 0;
}
