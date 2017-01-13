// https://www.codechef.com/problems/GERALD3
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


class Solution {
    struct Query {
        int l, r, id;
        int block_id;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N, M;
    string S;
    int64_t nowAns;
    int BLOCK_SIZE;
    vector<Query> queries;
    vector<int64_t> ans;
    set<int> idx;

    void move(int x, int sign) {
        // update nowAns
        int k = SuffixArray::pos[x];

        if (sign == -1) idx.erase(k);

        auto it = idx.lower_bound(k);
        int lcp = 0;
        if (it != idx.end()) {
            int j = *it;
            lcp = SuffixArray::calcLCP(x, SuffixArray::sa[j]);
        }
        if (it != idx.begin()) {
            int i = *(--it);
            lcp = max(lcp, SuffixArray::calcLCP(x, SuffixArray::sa[i]));
        }

        if (sign == 1) {
            nowAns += (N - x - lcp);
            idx.insert(k);
        } else {
            nowAns -= (N - x - lcp);
        } 
    }

public:
    Solution() {
        cin >> S;
        N = S.length();
        S += '$';

        scanf("%d", &M);
        BLOCK_SIZE = int(ceil(pow(double(N)*N/M, 0.5)));

        queries.resize(M);
        ans.resize(M);
        for (int i = 0; i < M; i++) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;
            queries[i].l = l;
            queries[i].r = r;
            queries[i].id = i;
            queries[i].block_id = l/BLOCK_SIZE;
        }

        SuffixArray::S = S.c_str();
        SuffixArray::buildSA();
        SuffixArray::buildLCP();
    }

    void solve() {
        sort(queries.begin(), queries.end());

        int l = 0, r = 0;
        nowAns = 0;

        for (int i = 0; i < (int)queries.size(); i++) {
            const Query& q = queries[i];
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
            ans[q.id] = nowAns;
        }

        for (int64_t x: ans) {
            printf("%lld\n", x);
        }
    }
};

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        Solution solution;
        solution.solve();
    }
    return 0;
}
