// https://leetcode.com/problems/alien-dictionary/
// 269. Alien Dictionary

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string alienOrder(vector<string> &words) {
        vector<vector<int>> adj(26);
        vector<bool> seen(26), vis(26), instack(26);
        for (const auto w: words) {
            for (char c: w) seen[c-'a'] = true;
        }
        dfs1(words, 0, 0, words.size(), adj);
        vector<int> ret;
        for (int i = 0; i < 26; i++) {
            if (seen[i] && !vis[i]) {
                bool ok = dfs2(adj, vis, instack, i, ret);
                if (!ok) return "";
            }
        }
        return convert(ret);
    }
private:
    void dfs1(const vector<string> &words, int d, int l, int r,
              vector<vector<int>> &adj) {
        if (r == l+1) return;
        int p = l;
        while (p < r) {
            while (p < r && words[p].length() <= d) p++;
            if (p == r) break;
            int q = p + 1;
            while (q < r &&
                   (int)words[q].length() > d &&
                   words[q][d] == words[p][d]) q++;
            dfs1(words, d+1, p, q, adj);
            if (q < r) addEdge(adj, words[p][d], words[q][d]);
            p = q;
        }
    }

    void addEdge(vector<vector<int>> &adj, char c1, char c2) {
        adj[c1-'a'].push_back(c2-'a');
    }

    bool dfs2(const vector<vector<int>> &adj,
              vector<bool> &vis, vector<bool> &instack,
              int u, vector<int> &ret) {
        instack[u] = true;
        vis[u] = true;
        for (int v: adj[u]) {
            if (instack[v]) return false;
            if (!vis[v]) {
                if (!dfs2(adj, vis, instack, v, ret)) return false;
            }
        }
        instack[u] = false;
        ret.push_back(u);
        return true;
    }

    string convert(const vector<int> &order) {
        string ret;
        for (int i = (int)order.size()-1; i >= 0; i--) {
            ret.push_back('a' + order[i]);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    vector<string> words = {"z", "z"};
    auto ret = solution.alienOrder(words);
    cout << ret << endl;
    return 0;
}
