// https://leetcode.com/problems/word-pattern-ii/
// 291. Word Pattern II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        map<char, string> fwd;
        map<string, char> bwd;
        return dfs(pattern, 0, str, 0, fwd, bwd);
    }

    bool dfs(const string &pattern, int p,
             const string &str, int q,
             map<char, string> &fwd,
             map<string, char> &bwd) {
        const int m = pattern.length();
        const int n = str.length();
        if (p == m && q == n) return true;
        if (p == m || q == n) return false;
        char ch = pattern[p];
        if (fwd.find(ch) != fwd.end()) {
            string s = fwd.at(ch);
            for (int e = q+1; e <= n; e++) {
                if (str.substr(q, e-q) == s) {
                    return dfs(pattern, p+1, str, e, fwd, bwd);
                }
            }
            return false;
        } else {
            for (int e = q+1; e <= n; e++) {
                string t = str.substr(q, e-q);
                if (bwd.find(t) == bwd.end()) {
                    fwd[ch] = t;
                    bwd[t] = ch;
                    if (dfs(pattern, p+1, str, e, fwd, bwd)) return true;
                    fwd.erase(ch);
                    bwd.erase(t);
                }
            }
            return false;
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
