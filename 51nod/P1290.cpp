// https://www.51nod.com/onlineJudge/questionCode.html#!problemId=1290
// 1290 Counting Diff Pairs

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using PII = pair<int, int>;

using namespace __gnu_pbds;
typedef tree<PII, null_type, less<PII>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

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
    int BLOCK_SIZE;
    int64_t currAns;
    vector<Query> queries;
    vector<int64_t> ans;

    ordered_set nums;

    void move(int pos, int sign) {
        int x = A[pos];
        if (sign == -1) nums.erase(make_pair(x, pos));
        int high = nums.order_of_key(make_pair(x + K + 1, -1));
        int low  = nums.order_of_key(make_pair(x - K, -1));
        int cnt = high - low;
        if (sign == 1) {
            currAns += cnt;
            nums.insert(make_pair(x, pos));
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
