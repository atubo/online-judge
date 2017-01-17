// https://www.51nod.com/onlineJudge/questionCode.html#!problemId=1290
// 1290 Counting Diff Pairs

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

class BIT {
public:
    // Note size needs to be power of 2
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        memset(tree, 0, (size+1) * sizeof(int64_t));
    }
    
    ~BIT() {
        free(tree);
        tree = NULL;
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

BIT fenwick(65536);

class Solution {
    struct Query {
        int l, r, id;
        int block_id;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N, K, Q;
    vector<int> A;
    int ND; // number of distinct elements
    vector<int> norm;
    vector<int> toOrig;
    vector<PII> normBounds; // normalized bounds, index is normalized value

    int BLOCK_SIZE;
    int64_t currAns;
    vector<Query> queries;
    vector<int64_t> ans;

    void move(int pos, int sign) {
        int x = norm[pos];
        int low, high;
        tie(low, high) = normBounds[x];
        if (sign == -1) fenwick.set(x+1, -1);
        int cnt = fenwick.get(high+1) - (low > 0 ? fenwick.get(low) : 0);
        if (sign == 1) {
            currAns += cnt;
            fenwick.set(x+1, 1);
        } else {
            currAns -= cnt;
        }
    }

public:
    Solution() {
        scanf("%d %d %d", &N, &K, &Q);

        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        norm.resize(N);
        toOrig.resize(N);

        normalize();

        BLOCK_SIZE = int(ceil(pow(double(N)*N/Q, 0.5)));
        queries.resize(Q);
        ans.resize(Q);
        for (int i = 0; i < Q; i++) {
            int l, r;
            scanf("%d %d", &l, &r);
            r++;
            queries[i].l = l;
            queries[i].r = r;
            queries[i].id = i;
            queries[i].block_id = l/BLOCK_SIZE;
        }
    }

    void normalize() {
        vector<PII> xAndPos(N);
        for (int i = 0; i < N; i++) {
            xAndPos[i] = make_pair(A[i], i);
        }
        sort(xAndPos.begin(), xAndPos.end());

        int idx = -1;
        for (int i = 0; i < N; i++) {
            if (i == 0 || xAndPos[i].first != xAndPos[i-1].first) {
                idx++;
            }
            norm[xAndPos[i].second] = idx;
            toOrig[idx] = xAndPos[i].first;
        }
        ND = idx + 1;
        toOrig.resize(ND);

        normBounds.resize(ND);
        for (int i = 0; i < ND; i++) {
            int high = toOrig[i] + K;
            auto it = lower_bound(toOrig.begin(), toOrig.end(), high);
            if (it == toOrig.end() || *it > high) --it;
            int highVal = it - toOrig.begin();

            int low = toOrig[i] - K;
            it = lower_bound(toOrig.begin(), toOrig.end(), low);
            int lowVal = it - toOrig.begin();
            normBounds[i] = make_pair(lowVal, highVal);
        }
    }

    void solve() {
        sort(queries.begin(), queries.end());

        int l = 0, r = 0;
        currAns = 0;

        for (int i = 0; i < (int)queries.size(); i++) {
            const Query& q = queries[i];
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
            ans[q.id] = currAns;
        }

        for (auto x: ans) {
            printf("%lld\n", x);
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
