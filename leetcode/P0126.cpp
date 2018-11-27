// https://leetcode.com/problems/word-ladder-ii/
// 126. Word Ladder II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool connect(const string &w, const string &v) {
        int cnt = 0;
        for (int i = 0; i < (int)w.length(); i++) {
            if (w[i] != v[i]) cnt++;
            if (cnt > 1) return false;
        }
        return true;
    }

    vector<vector<string>> findLadders(string beginWord,
                                       string endWord,
                                       vector<string> &wordList) {
        wordList.push_back(beginWord);
        const int n = wordList.size();
        vector<vector<int>> adj(n);
        vector<vector<string>> ret;
        int dst = -1;
        for (int i = 0; i < n; i++) {
            const string w = wordList[i];
            if (w == endWord) dst = i;
            for (int j = i+1; j < n; j++) {
                const string v = wordList[j];
                if (connect(w, v)) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        if (dst == -1) return ret;

        vector<int> dist(n, INT_MAX);
        bfs(n-1, dst, adj, dist);
        if (dist[n-1] == INT_MAX) return ret;
        printf("bfs done d=%d\n", dist[n-1]);
        vector<bool> vis(n);
        vector<string> path;
        dfs(n-1, dst, wordList, adj, vis, dist, path, ret);
        return ret;
    }

    void bfs(int start, int end, const vector<vector<int>> &adj,
             vector<int> &dist) {
        queue<pair<int, int>> q;
        const int n = adj.size();
        vector<bool> vis(n);
        q.push(make_pair(end, 0));
        vis[end] = true;
        dist[end] = 0;
        while (!q.empty()) {
            int u, d;
            tie(u,d) = q.front();
            dist[u] = d;
            q.pop();
            if (u == start) return;
            for (int v: adj[u]) {
                if (!vis[v]) {
                    q.push(make_pair(v, d+1));
                    vis[v] = true;
                }
            }
        }
    }

    void dfs(int u, int end,
             const vector<string> &wordList,
             const vector<vector<int>> &adj,
             vector<bool> &vis,
             const vector<int> &dist,
             vector<string> &path,
             vector<vector<string>> &ret) {
        if (u == end) {
            path.push_back(wordList[u]);
            ret.push_back(path);
            path.pop_back();
            return;
        }

        vis[u] = true;
        path.push_back(wordList[u]);
        for (int v: adj[u]) {
            if (!vis[v] && dist[v] == dist[u]-1) {
                dfs(v, end, wordList, adj, vis, dist, path, ret);
            }
        }
        path.pop_back();
        vis[u] = false;
    }
};

int main() {
    string b, e;
    cin >> b >> e;
    int n;
    cin >> n;
    vector<string> wl(n);
    for (int i = 0; i < n; i++) {
        cin >> wl[i];
    }
    Solution solution;
    auto ret = solution.findLadders(b, e, wl);
    for (auto path: ret) {
        for (auto w: path) {
            printf("%s ", w.c_str());
        }
        printf("\n");
    }
    return 0;
}
