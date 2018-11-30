// https://leetcode.com/problems/alien-dictionary/
// 269. Alien Dictionary

#include <bits/stdc++.h>
using namespace std;

class Solution {
    const static int SZ = 26;
public:
    string alienOrder(vector<string> &words) {
        vector<bool> seen(26);
        for (const auto &w: words) {
            for (char c: w) {
                seen[c-'a'] = true;
            }
        }
        const int n = words.size();
        vector<vector<int>> adj(SZ);
        for (int i = 0; i < n-1; i++) {
            int u, v;
            tie(u, v) = process(words[i], words[i+1]);
            if (u >= 0) adj[u].push_back(v);
        }
        string ret;
        if (hasCycle(adj)) return ret;
        stack<int> st;
        vector<bool> vis(SZ);
        for (int i = 0; i < SZ; i++) {
            if (!vis[i] && seen[i]) dfs2(adj, i, vis, st);
        }
        while (!st.empty()) {
            ret.push_back('a' + st.top());
            st.pop();
        }
        return ret;
    }

private:
    pair<int, int> process(const string &w1, const string &w2) {
        if (w1 == w2) return {-1, -1};
        int l1 = w1.length();
        int l2 = w2.length();
        for (int i = 0; i < min(l1, l2); i++) {
            if (w1[i] != w2[i]) return make_pair(w1[i]-'a', w2[i]-'a');
        }
        return make_pair(-1, -1);
    }

    bool hasCycle(const vector<vector<int>> &adj) {
        vector<bool> vis(SZ);
        vector<bool> instack(SZ);
        for (int u = 0; u < SZ; u++) {
            if (!vis[u]) {
                if (dfs1(adj, u, vis, instack)) return true;
            }
        }
        return false;
    }

    bool dfs1(const vector<vector<int>> &adj, int u,
              vector<bool> &vis, vector<bool> & instack) {
        vis[u] = true;
        instack[u] = true;
        for (int v: adj[u]) {
            if (instack[v]) return true;
            if (!vis[v]) {
                if (dfs1(adj, v, vis, instack)) return true;
            }
        }
        instack[u] = false;
        return false;
    }

    void dfs2(const vector<vector<int>> &adj, int u,
              vector<bool> &vis, stack<int> &st) {
        vis[u] = true;
        for (int v: adj[u]) {
            if (!vis[v]) {
                dfs2(adj, v, vis, st);
            }
        }
        st.push(u);
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    Solution solution;
    auto ret = solution.alienOrder(words);
    cout << ret << endl;
    return 0;
}
