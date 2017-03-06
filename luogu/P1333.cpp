// https://www.luogu.org/problem/show?pid=1333
// 瑞瑞的木棍

#include <bits/stdc++.h>
using namespace std;
using Adj = vector<vector<int> >;
using PII = pair<int, int>;

map<string, int> toId;
Adj adj;
int N;

bool bfs() {
    vector<bool> visited(N, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: adj[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
            }
        }
    }

    bool ret = true;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            ret = false;
            break;
        }
    }

    return ret;
}

bool solve() {
    if (N == 0) return true;
    bool possible = bfs();
    if (!possible) return false;

    int oddCount = 0;
    for (int i = 0; i < N; i++) {
        oddCount += (adj[i].size() & 1);
    }

    return oddCount == 0 || oddCount == 2;
}

int main() {
    char a[11], b[11];
    vector<PII> edges;
    while (scanf("%s %s", a, b) == 2) {
        if (toId.count(a) == 0) {
            toId.insert(make_pair(a, toId.size()));
        }
        if (toId.count(b) == 0) {
            toId.insert(make_pair(b, toId.size()));
        }
        edges.push_back(make_pair(toId.at(a), toId.at(b)));
    }
    N = toId.size();
    adj.resize(N);
    for (const auto& e: edges) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool possible = solve();
    printf("%s\n", possible ? "Possible" : "Impossible");

    return 0;
}
