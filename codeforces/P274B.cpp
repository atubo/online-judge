// http://codeforces.com/problemset/problem/274/B
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using Adj = vector<vector<int>>;
private:
    int N;
    vector<int> V;
    Adj adj;
public:
    Solution() {
        cin >> N;
        V.resize(N);
        adj.resize(N);
        for (int i = 0; i < N-1; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < N; i++) {
            cin >> V[i];
        }
    }

    void solve() {
        vector<bool> visited(N, false);
        vector<int64_t> count(N);
        dfs(0, visited, count);
        cout << count[0] << endl;
    }

    void dfs(int u, vector<bool>& visited, vector<int64_t>& count) {
        visited[u] = true;
        bool found = false;
        int64_t maxdown = -1, maxup = -1;
        for (int v: adj[u]) {
            if (!visited[v]) {
                dfs(v, visited, count);
                int64_t up = (count[v] - V[v]) / 2;
                int64_t down = count[v] - up;
                assert(up >= 0 && down >= 0);
                maxdown = max(maxdown, down);
                maxup = max(maxup, up);
                found = true;
            }
        }
        if (found) {
            count[u] = maxdown + maxup + abs(V[u] - maxdown + maxup);
        } else {
            count[u] = abs(V[u]);
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}


