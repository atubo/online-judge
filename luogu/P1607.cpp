// https://www.luogu.org/problem/show?pid=1607
// [USACO09FEB]庙会班车Fair Shuttle

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

class Solution {
private:
    map<int, int> dest;
    vector<vector<PII>> groups;
    int K, N, C;
    int space, ans;
public:
    Solution() {
        scanf("%d%d%d", &K, &N, &C);
        groups.resize(N+1);
        for (int i = 0; i < K; i++) {
            int s, e, m;
            scanf("%d%d%d", &s, &e, &m);
            groups[s].push_back(make_pair(e, m));
        }

        space = C;
        ans = 0;
    }

    void solve() {
        for (int i = 1; i <= N; i++) {
            unboard(i);
            for (const PII& g: groups[i]) {
                board(g.first, g.second);
            }
        }
        printf("%d\n", ans);
    }

    void unboard(int s) {
        if (dest.empty() || dest.begin()->first > s) return;
        space += dest.begin()->second;
        dest.erase(dest.begin());
    }

    void board(int e, int m) {
        if (space >= m) {
            space -= m;
            ans += m;
            dest[e] += m;
        } else {
            int k = evict(e, m - space);
            dest[e] += space + k;
            ans += space;
            space = 0;
        }
    }

    int evict(int e, int k) {
        int ret = 0;
        while (!dest.empty() && k > 0) {
            auto it = dest.end();
            --it;
            if (it->first <= e) break;
            if (it->second <= k) {
                k -= it->second;
                ret += it->second;
                dest.erase(it);
            } else {
                it->second -= k;
                ret += k;
                k = 0;
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
