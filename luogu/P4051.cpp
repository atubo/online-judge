// https://www.luogu.org/problemnew/show/P4051
// [JSOI2007]字符加密

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
    int NP;

    bool sufCmp(int i, int j)
    {
        if (pos[i] != pos[j])
            return pos[i] < pos[j];
        //i += gap;
        //j += gap;
        //return (i < N && j < N) ? pos[i] < pos[j] : i > j;
        i = (i + gap) % N;
        j = (j + gap) % N;
        return pos[i] < pos[j];
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
const int MAXN = 100010;
int N;
char ans[MAXN];

int main() {
    string s;
    cin >> s;
    N = s.length();
    SuffixArray::S = s.c_str();
    SuffixArray::buildSA();
    for (int i = 0; i < N; i++) {
        int p = (SuffixArray::sa[i] + N - 1) % N;
        ans[i] = s[p];
    }
    printf("%s\n", ans);
    return 0;
}
