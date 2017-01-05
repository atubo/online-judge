// http://www.lydsy.com/JudgeOnline/problem.php?id=2038
// 2038: [2009国家集训队]小Z的袜子(hose)

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

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
    int BLOCK_SIZE;
    vector<Query> queries;
    vector<pair<int64_t, int64_t> > ans;

    vector<int> colors;
    vector<int> count;
    int64_t total;
    int64_t numer, denom;

    void move(int pos, int sign) {
        int c = colors[pos];
        if (sign == 1) {
            numer += count[c]++;
            denom += total++;
        } else {
            numer -= --count[c];
            denom -= --total;
        }
    }

public:
    Solution() {
        scanf("%d %d", &N, &M);
        BLOCK_SIZE = int(ceil(pow(N, 0.5)));

        colors.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &colors[i]);
        }

        count.resize(N+1);
        total = 0;

        queries.resize(M);
        for (int i = 0; i < M; i++) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;
            Query& q = queries[i];
            q.l = l;
            q.r = r;
            q.id = i;
            q.block_id = l/BLOCK_SIZE;
        }

        ans.resize(M);
    }

    void solve() {
        sort(queries.begin(), queries.end());

        int l = 0, r = 0;
        numer = 0, denom = 0;

        for (int i = 0; i < (int)queries.size(); i++) {
            const Query& q = queries[i];
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
            ans[q.id] = normalize(numer, denom);
        }

        for (int i = 0; i < M; i++) {
            printf("%lld/%lld\n", ans[i].first, ans[i].second);
        }
    }

    pair<int64_t, int64_t> normalize(int64_t a, int64_t b) {
        if (a == 0) return make_pair(0, 1);
        int64_t g = gcd(a, b);
        return make_pair(a/g, b/g);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
