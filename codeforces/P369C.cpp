// http://codeforces.com/problemset/problem/369/C
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
    using Adj = vector<vector<PII>>;
private:
    int N;
    Adj adj;
    vector<bool> fix;
public:
    Solution() {
        cin >> N;
        adj.resize(N);
        for (int i = 0; i < N-1; i++) {
            int x, y, t;
            scanf("%d %d %d", &x, &y, &t);
            x--; y--;
            adj[x].push_back(make_pair(y, t));
            adj[y].push_back(make_pair(x, t));
        }
        fix.resize(N, false);
    }

    bool dfs(int u, bool bad, vector<bool>& visited) {
        visited[u] = true;
        bool descBad = false;
        for (const PII& p: adj[u]) {
            int v, t;
            tie(v, t) = p;
            if (!visited[v]) {
                descBad |= dfs(v, t == 2, visited);
            }
        }
        if (bad && !descBad) fix[u] = true;
        return bad | descBad;
    }

    void solve() {
        vector<bool> visited(N, false);
        dfs(0, false, visited);
        vector<int> ret;
        for (int i = 0; i < N; i++) {
            if (fix[i]) ret.push_back(i+1);
        }
        cout << ret.size() << endl;
        for (int x: ret) {
            cout << x << " ";
        }
        cout << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
