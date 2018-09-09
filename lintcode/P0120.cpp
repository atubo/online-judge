// https://www.lintcode.com/problem/word-ladder/description?_from=ladder&&fromId=23
// 120. Word Ladder
#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int ladderLength(string &start, string &end, unordered_set<string> &dict) {
        return bfs(start, end, dict);
    }

    int bfs(const string &start, const string &end, unordered_set<string> dict) {
        if (start == end) return 1;
        vector<string> dv;
        for (const auto &w: dict) {
            if (w != end && w != start) dv.push_back(w);
        }
        dv.push_back(end);
        dv.push_back(start);
        const int n = dv.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (neighbor(dv[i], dv[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        vector<bool> vis(n);
        queue<pair<int, int>> q;
        q.push(make_pair(n-1, 1));
        vis[n-1] = true;
        while (!q.empty()) {
            int s, d;
            tie(s, d) = q.front();
            q.pop();
            if (s == n-2) return d;
            for (int v: adj[s]) {
                if (!vis[v]) {
                    q.push(make_pair(v, d+1));
                    vis[v] = true;
                }
            }
        }
        return 0;
    }

    bool neighbor(const string &s, const string &w) {
        int ret = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] != w[i]) ret++;
            if (ret > 1) return false;
        }
        return true;
    }
};

int main() {
    Solution solution;
    string start = getString();
    string end = getString();
    auto wordlist = getStringVector();
    unordered_set<string> dict;
    for (const auto& w: wordlist) {
        dict.insert(w);
    }
    cout << solution.ladderLength(start, end, dict) << endl;
    return 0;
}
