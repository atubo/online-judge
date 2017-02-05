// https://www.luogu.org/problem/show?pid=1273
// 有线电视网

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
typedef vector<vector<PII> > Adj;

const int MINF = -1e9;

class Solution {
private:
    int N, M;
    Adj adj;
    vector<int> pay;
    vector<vector<int> > dp;
    vector<int> leaves;

public:
    Solution() {
        scanf("%d %d", &N, &M);
        adj.resize(N);
        for (int i = 0; i < N-M; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                int a, c;
                scanf("%d %d", &a, &c);
                a--;
                adj[i].push_back(make_pair(a, c));
            }
        }
        pay.resize(M);
        for (int i = 0; i < M; i++) {
            scanf("%d", &pay[i]);
        }

        leaves.resize(N);
        dfs1(0);
    }

    void dfs1(int u) {
        if (u >= N-M) {
            leaves[u] = 1;
            return;
        }
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            dfs1(v);
            leaves[u] += leaves[v];
        }
    }

    void solve() {
        dp.resize(N);

        dfs2(0);
        int ans;
        for (ans = leaves[0]; ans > 0; ans--) {
            if (dp[0][ans] >= 0) break;
        }
        printf("%d\n", ans);
    };

    void dfs2(int u) {
        if (u >= N-M) {
            dp[u].resize(2);
            dp[u][0] = 0;
            dp[u][1] = pay[u-N+M];
            return;
        }
        int K = leaves[u];
        dp[u].resize(K+1, MINF);
        dp[u][0] = 0;
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            dfs2(v);
            for (int k = K; k >= 1; k--) {
                for (int kv = 1; kv < (int)dp[v].size(); kv++) {
                    if (kv > k) break;
                    dp[u][k] = max(dp[u][k], dp[v][kv] - w + dp[u][k-kv]);
                }
            }
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}

