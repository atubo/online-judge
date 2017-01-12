// http://codeforces.com/problemset/problem/86/D

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int freq[MAXN+1];

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
    int64_t nowAns;
    int BLOCK_SIZE;
    vector<Query> queries;
    vector<int64_t> ans;

    void move(int pos, int sign) {
        if (sign == 1) {
            nowAns += (2LL * (freq[A[pos]]++) + 1) * A[pos];
        } else {
            nowAns -= (2LL * (freq[A[pos]]--) - 1) * A[pos];
        }
    }

public:
    Solution() {
        scanf("%d %d", &N, &Q);

        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }

        BLOCK_SIZE = int(ceil(pow(double(N)*N/Q, 0.5)));
        // set up queries;
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

        for (int64_t x: ans) {
            cout << x << endl;
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
