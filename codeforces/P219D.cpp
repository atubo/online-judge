// http://codeforces.com/problemset/problem/219/D
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
    using Adj = vector<vector<PII>>;
private:
    int N;
    Adj adj;
    vector<int> inv;
public:
    Solution() {
        cin >> N;
        adj.resize(N);
        for (int i = 0; i < N-1; i++) {
            int s, t;
            scanf("%d %d", &s, &t);
            s--; t--;
            adj[s].push_back(make_pair(t, 1));
            adj[t].push_back(make_pair(s, -1));
        }
        inv.resize(N);
    }

    void findRootInv() {
        vector<bool> visited(N, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const PII& p: adj[u]) {
                int v, d;
                tie(v, d) = p;
                if (!visited[v]) {
                    if (d == -1) inv[0]++;
                    q.push(v);
                    visited[v] = true;
                }
            }
        }
    }

    void solve() {
        findRootInv();
        vector<bool> visited(N, false);
        dfs(0, inv[0], visited);
        int minInv = *min_element(inv.begin(), inv.end());
        cout << minInv << endl;
        for (int i = 0; i < N; i++) {
            if (inv[i] == minInv) cout << i+1 << " ";
        }
        cout << endl;
    }

    void dfs(int u, int currInv, vector<bool>& visited) {
        inv[u] = currInv;
        visited[u] = true;
        for (const PII& p: adj[u]) {
            int v, d;
            tie(v, d) = p;
            if (!visited[v]) {
                dfs(v, currInv + d, visited);
            }
        }
    }

};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
