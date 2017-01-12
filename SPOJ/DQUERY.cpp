// http://www.spoj.com/problems/DQUERY/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int counter[MAXN+1];

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

    void move(int pos, int sign) {
        // update nowAns
        if (sign == 1) {
            nowAns += (++counter[A[pos]] == 1);
        } else {
            nowAns -= (--counter[A[pos]] == 0);
        }
    }

public:
    Solution() {
        scanf("%d", &N);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }

        scanf("%d", &Q);
        BLOCK_SIZE = int(ceil(pow(double(N)*N/Q, 0.5)));
        // set up queries
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
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
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
