// https://www.luogu.org/problem/show?pid=1341
// 无序字母对
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
typedef vector<vector<PII> > Adj;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int idx(char c) {
    for (int i = 0; i < 52; i++) {
        if (c == ALPHABET[i]) return i;
    }
    assert(0);
    return -1;
}

bool dfs(int u, int e, const Adj adj, vector<bool>& visited, string& ans, int n) {
    ans += ALPHABET[u];
    if (e >= 0) visited[e] = true;
    if (n == 0) return true;
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i].first;
        int en = adj[u][i].second;
        if (!visited[en]) {
            if (dfs(v, en, adj, visited, ans, n-1)) return true;
        }
    }
    visited[e] = false;
    ans.erase(ans.size()-1);
    return false;
}

int main() {
    int N;
    cin >> N;
    string str;
    Adj adj(52);
    for (int i = 0; i < N; i++) {
        cin >> str;
        int u = idx(str[0]);
        int v = idx(str[1]);
        adj[u].push_back(make_pair(v, i));
        adj[v].push_back(make_pair(u, i));
    }

    int oddNodes = 0;
    for (int i = 0; i < 52; i++) {
        sort(adj[i].begin(), adj[i].end());
        if (adj[i].size() & 1) oddNodes++;
    }
    if (oddNodes != 0 && oddNodes != 2) {
        cout << "No Solution" << endl;
        return 0;
    }

    vector<bool> visited(N, false);
    string ans;
    for (int i = 0; i < 52; i++) {
        if (adj[i].size() > 0 && (oddNodes == 0 || (adj[i].size() & 1))) {
            ans.clear();
            if (dfs(i, -1, adj, visited, ans, N)) break;
        }
    }
    cout << ans << endl;
    return 0;
}
