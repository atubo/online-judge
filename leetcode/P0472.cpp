// https://leetcode.com/problems/concatenated-words/#/description
// 472. Concatenated Words
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        sort(words.begin(), words.end(),
             [](const string& s, const string& t){return s.length() < t.length();});
        vector<string> ret;
        set<string> dict;
        for (auto w: words) {
            if (w.empty()) continue;
            if (canBreak(w, dict)) {
                ret.push_back(w);
            } else {
                dict.insert(w);
            }
        }
        return ret;
    }

    bool canBreak(const string& word, const set<string>& dict) {
        const int N = word.length();
        vector<int> dp(N, -1);
        return solve(word, 0, dict, dp) == 1;
    }

    int solve(const string& word, int pos, const set<string>& dict,
              vector<int>& dp) {
        const int N = word.length();
        if (pos == N) return 1;
        if (dp[pos] >= 0) return dp[pos];
        int& ret = dp[pos] = 0;
        for (int q = pos+1; q <= N; q++) {
            string prefix = word.substr(pos, q-pos);
            if (dict.count(prefix) > 0 &&
                solve(word, q, dict, dp)) {
                ret = 1;
                break;
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    vector<string> words = getStringVector();
    auto ret = solution.findAllConcatenatedWordsInADict(words);
    for (auto w: ret) {
        cout << w << endl;
    }
    return 0;
}
