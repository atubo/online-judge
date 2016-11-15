// http://codeforces.com/problemset/problem/120/F
#include <bits/stdc++.h>

using namespace std;

class Solution {
    using Adj = vector<vector<int>>;
    using PII = pair<int, int>;
private:
    int N;
    Adj adj;
public:
    void solve() {
        ifstream in("input.txt");
        in >> N;
        int ret = 0;
        for (int i = 0; i < N; i++) {
            ret += dia(in);
        }
        ofstream out("output.txt");
        out << ret << endl;
    }

    int dia(ifstream& in) {
        adj.clear();
        int M;
        in >> M;
        adj.resize(M);
        for (int i = 0; i < M-1; i++) {
            int u, v;
            in >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        PII p = bfs(0);
        p = bfs(p.second);
        return p.first;
    }

    PII bfs(int s) {
        const int M = adj.size();
        vector<bool> visited(M, false);
        queue<PII> q;
        q.push(make_pair(0, s));
        visited[s] = true;
        PII last;
        while (!q.empty()) {
            int d, u;
            tie(d, u) = last = q.front();
            q.pop();
            for (int v: adj[u]) {
                if (!visited[v]) {
                    q.push(make_pair(d+1, v));
                    visited[v] = true;
                }
            }
        }
        return last;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
