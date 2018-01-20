// https://www.luogu.org/problemnew/show/3181
// [HAOI2016]找相同字符

#include <bits/stdc++.h>
using namespace std;



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

const int MAXN = 400010;
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
    s1 += '{';
    s2 += '}';
    N1 = s1.length();
    string s = s1 + s2;
    SuffixArray::S = s.c_str();
    SuffixArray::buildSA();
    SuffixArray::buildLCP();

    int64_t ans = 0;
    for (int i = 0; i < SuffixArray::N-2; i++) {
        int cnt[2];
        int from = whichString(SuffixArray::sa[i]);
        cnt[from] = 1; cnt[1-from] = 0;
        int64_t lcp = SuffixArray::lcp[i];
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
