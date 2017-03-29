// https://www.luogu.org/problem/show?pid=3252
// [JLOI2012]树

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<vector<int>> children;
    int N, S;
    vector<int> weight, ps;
    int ret, curr;

    void dfs(int u, int f) {
        int total = ps[curr] = ps[curr-1] + weight[u];
        curr++;
        auto it = lower_bound(ps.begin(), ps.begin() + curr, total - S);
        if (it != ps.begin() + curr && *it == total - S) ret++;
        for (int v: children[u]) {
            if (v != f) {
                dfs(v, u);
            }
        }
        curr--;
    }

public:
    Solution() {
        scanf("%d %d", &N, &S);
        children.resize(N+1);
        weight.resize(N+1);
        ps.resize(N+1);
        for (int i = 1; i <= N; i++){
            scanf("%d", &weight[i]);
        }
        for (int i = 1; i <= N-1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            children[u].push_back(v);
            children[v].push_back(u);
        }
        ret = 0;
        curr = 0;
    }

    void solve() {
        curr = 1;
        dfs(1, 0);
        printf("%d\n", ret);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
