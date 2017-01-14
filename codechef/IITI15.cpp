// https://www.codechef.com/problems/IITI15
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using PII = pair<int, int>;
typedef tree<int, null_type, less<int>, rb_tree_tag,
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
    int N, Q;
    vector<int> A;
    int nowAns, BLOCK_SIZE;
    vector<Query> queries;
    vector<int> ans;
    ordered_set nums;

    void move(int pos, int sign, bool left) {
        int x = A[pos];
        if (sign == -1) {
            nums.erase(x);
        }
        int below = nums.order_of_key(x);
        int above = nums.size() - below;
        if (sign == 1) {
            nowAns += (left ? below : above);
            nums.insert(x);
        } else {
            nowAns -= (left ? below : above);
        }
    }

public:
    Solution() {
        scanf("%d", &N);
        vector<PII> B(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &B[i].first);
            B[i].second = i;
        }
        sort(B.begin(), B.end());
        A.resize(N);
        for (int i = 0; i < N; i++) {
            const auto& p = B[i];
            A[p.second] = i;
        }

        scanf("%d", &Q);
        BLOCK_SIZE = int(ceil(pow(double(N)*N/Q, 0.5)));
        queries.resize(Q);
        ans.resize(Q);

        for (int i = 0; i < Q; i++) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;
            queries[i].l = l;
            queries[i].r = r;
            queries[i].id = i;
            queries[i].block_id = l/BLOCK_SIZE;
        }
    }

    void solve() {
        sort(queries.begin(), queries.end());

        int l = 0, r = 0;
        nowAns = 0;

        for (int i = 0; i < (int)queries.size(); i++) {
            const Query& q = queries[i];
            while (l > q.l) move(--l, 1, true);
            while (r < q.r) move(r++, 1, false);
            while (l < q.l) move(l++, -1, true);
            while (r > q.r) move(--r, -1, false);
            ans[q.id] = nowAns;
        }

        for (int x: ans) {
            printf("%d\n", x);
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
