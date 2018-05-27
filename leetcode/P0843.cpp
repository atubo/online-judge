// https://leetcode.com/problems/guess-the-word/description/
// 843. Guess the Word

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Master {
public:
    Master(const string &secret): len_(secret.length()), secret_(secret) {}

    int guess(string word) {
        int ans = 0;
        for (int i = 0; i < len_; i++) {
            if (secret_[i] == word[i]) ans++;
        }
        return ans;
    }
private:
    int len_;
    const string secret_;
};

class Solution {
    using Adj = vector<map<int, vector<int>>>;
public:
    void findSecretWord(vector<string> &wordlist, Master &master) {
        const int N = wordlist.size();
        Adj adj(N);
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                int match = numMatches(wordlist[i], wordlist[j]);
                adj[i][match].push_back(j);
                adj[j][match].push_back(i);
            }
        }
        vector<bool> vis(N);
        int start = 83 % N;
        dfs(wordlist, master, adj, start, vis);
    }

    int numMatches(const string &s, const string &t) {
        int ans = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            ans += (s[i] == t[i]);
        }
        return ans;
    }

    bool dfs(const vector<string> &wordlist, Master &master,
             const Adj &adj, int u, vector<bool> &vis) {
        //printf("in dfs\n");
        vis[u] = true;
        int m = master.guess(wordlist[u]);
        if (m == 6) {
            //printf("found!\n");
            return true;
        }
        for (const auto &p: adj[u]) {
            if (p.first == m) continue;
            for (int v: p.second) vis[v] = true;
        }
        for (int v: adj[u].at(m)) {
            if (!vis[v]) {
                if (dfs(wordlist, master, adj, v, vis)) return true;
            }
        }
        return false;
    }
};

int main() {
    string secret = getString();
    vector<string> wordlist = getStringVector();
    Master master(secret);
    Solution solution;
    solution.findSecretWord(wordlist, master);
    return 0;
}


