// http://codeforces.com/problemset/problem/61/D
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
    using Adj = vector<vector<PII>>;
private:
    int N;
    Adj adj;
    vector<int64_t> oneway, roundtrip;
public:
    Solution() {
        cin >> N;
        adj.resize(N);
        for (int i = 0; i < N-1; i++) {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            x--; y--;
            adj[x].push_back(make_pair(y, w));
            adj[y].push_back(make_pair(x, w));
        }
        oneway.resize(N);
        roundtrip.resize(N);
    }

    void dfs(int u, vector<bool>& visited) {
        visited[u] = true;
        vector<int64_t> rt, diff;
        for (const PII& nbr: adj[u]) {
            int v, w;
            tie(v, w) = nbr;
            if (!visited[v]) {
                dfs(v, visited);
                rt.push_back(2*w + roundtrip[v]);
                diff.push_back(w + roundtrip[v] - oneway[v]);
            }
        }
        roundtrip[u] = accumulate(rt.begin(), rt.end(), (int64_t)0);
        oneway[u] = (diff.empty() ?
                     0 : roundtrip[u] - *max_element(diff.begin(), diff.end()));
    }

    void solve() {
        vector<bool> visited(N, false);
        dfs(0, visited);
        cout << oneway[0] << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
