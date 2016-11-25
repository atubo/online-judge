// http://codeforces.com/problemset/problem/461/B
#include <bits/stdc++.h>
using namespace std;

// (g, x, y) that a*x + b*y = g
tuple<int64_t, int64_t, int64_t> ext_gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    }
    int64_t dp, xp, yp;
    tie(dp, xp, yp) = ext_gcd(b, a % b);
    return make_tuple(dp, yp, xp - a / b * yp);
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    tie(d, xp, yp) = ext_gcd(a, n);
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

class Solution {
    using Adj = vector<vector<int>>;
private:
    int N;
    Adj adj;
    vector<bool> colorBlack;
    vector<int64_t> white, black;

    static const int64_t MOD = 1000000007;
public:
    Solution() {
        cin >> N;
        adj.resize(N);
        for (int i = 0; i < N-1; i++) {
            int p;
            scanf("%d", &p);
            adj[i+1].push_back(p);
            adj[p].push_back(i+1);
        }
        colorBlack.resize(N);
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            colorBlack[i] = x;
        }
        white.resize(N);
        black.resize(N);
    }

    int64_t add(int64_t a, int64_t b) {
        return (a + b) % MOD;
    }

    int64_t mul(int64_t a, int64_t b) {
        return (a * b) % MOD;
    }

    int64_t calcWhiteNodeBlackCount(int64_t prod,
                                    const vector<int64_t>& subwhite,
                                    const vector<int64_t>& subblack) {
        int64_t total = 0;
        for (int i = 0; i < (int)subwhite.size(); i++) {
            total = add(total,
                        mul(subblack[i], mod_solve(add(subwhite[i], subblack[i]),
                                                   1, MOD)));
        }
        return mul(total, prod);
    }

    void dfs(int u, vector<bool>& visited) {
        visited[u] = true;
        vector<int64_t> subwhite, subblack;
        for (int v: adj[u]) {
            if (!visited[v]) {
                dfs(v, visited);
                subwhite.push_back(white[v]);
                subblack.push_back(black[v]);
            }
        }

        int64_t prod = 1;
        for (int i = 0; i < (int)subwhite.size(); i++) {
            prod = mul(prod, add(subwhite[i], subblack[i]));
        }
        if (!colorBlack[u]) {
            white[u] = prod;
            black[u] = calcWhiteNodeBlackCount(prod, subwhite, subblack);
        } else {
            white[u] = 0;
            black[u] = prod;
        }
    }

    void solve() {
        vector<bool> visited(N, false);
        dfs(0, visited);
        cout << black[0] << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
