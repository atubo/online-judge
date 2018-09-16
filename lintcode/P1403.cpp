// https://www.lintcode.com/problem/maximum-product-path/description
// 1403. Maximum Product Path

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    static const int MOD = 1e9+7;
public:
    int getProduct(vector<int> &x, vector<int> &y, vector<int> &d) {
        const int n = d.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n-1; i++) {
            int u = x[i]-1, v = y[i]-1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int ans = 0;
        dfs(0, -1, adj, d, 1, ans);
        return ans;
    }

    void dfs(int u, int fa,
             const vector<vector<int>> &adj,
             const vector<int> &d,
             int prod, int &ans) {
        prod = mul(prod, d[u]);
        bool is_leaf = true;
        for (int v: adj[u]) {
            if (v != fa) {
                is_leaf = false;
                dfs(v, u, adj, d, prod, ans);
            }
        }
        if (is_leaf) {
            ans = max(ans, prod);
        }
    }

    int mul(int64_t a, int64_t b) {
        return ((a * b) % MOD + MOD) % MOD;
    }
};

int main() {
    printf("%d\n", (-1) % int(1e9+7));
    Solution solution;
    return 0;
}
