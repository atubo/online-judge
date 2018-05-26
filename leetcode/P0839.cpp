// https://leetcode.com/problems/similar-string-groups/description/
// 839. Similar String Groups

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Solution {
public:
    int numSimilarGroups(vector<string> &A) {
        const int N = A.size();
        vector<vector<int>> g(N);
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                if (isSimilar(A[i], A[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        return findGroupNum(g);
    }

    bool isSimilar(const string &s, const string &t) {
        const int L = s.length();
        int p = 0, q = L-1;
        while (s[p] == t[p]) p++;
        while (s[q] == t[q]) q--;
        if (s[p] != t[q] || s[q] != t[p]) return false;
        p++;
        while (p < q) {
            if (s[p] != t[p]) return false;
            p++;
        }
        return true;
    }

    int findGroupNum(const vector<vector<int>> &g) {
        const int N = g.size();
        vector<bool> vis(N, false);
        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                ans++;
                dfs(g, vis, i);
            }
        }
        return ans;
    }

    void dfs(const vector<vector<int>> &g, vector<bool>& vis, int u) {
        vis[u] = true;
        for (int v: g[u]) {
            if (!vis[v]) dfs(g, vis, v);
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    Solution solution;
    cout << solution.numSimilarGroups(A) << endl;
    return 0;
}
