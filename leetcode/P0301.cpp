// https://leetcode.com/problems/remove-invalid-parentheses/
// 301. Remove Invalid Parentheses

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int lp, rp;
        tie(lp, rp) = preprocess(s);
        vector<string> ret;
        string prefix;
        search(s, lp, rp, 0, 0, 0, prefix, ret);
        return ret;
    }

    pair<int, int> preprocess(const string &s) {
        int lp = 0, rp = 0;
        for (char c: s) {
            if (c == '(') lp++;
            if (c == ')') {
                if (lp == 0) rp++;
                else lp--;
            }
        }
        return make_pair(lp, rp);
    }

    void search(const string &s, int lp, int rp, int l, int r, int pos,
                string &prefix, vector<string> &ret) {
        const int n = s.length();
        if (lp < 0 || rp < 0 || r > l) return;
        if (pos == n) {
            if (lp == 0 && rp == 0 && l == r) {
                ret.push_back(prefix);
            }
            return;
        }
        if (s[pos] == '(') {
            int q = pos + 1;
            while (q < n && s[q] == '(') q++;
            search(s, lp-(q-pos), rp, l, r, q, prefix, ret);
            for (int k = 1; k <= q-pos; k++) {
                prefix.push_back('(');
                search(s, lp-(q-pos)+k, rp, l+k, r, q, prefix, ret);
            }
            for (int k = 1; k <= q-pos; k++) prefix.pop_back();
        } else if (s[pos] == ')') {
            int q = pos + 1;
            while (q < n && s[q] == ')') q++;
            search(s, lp, rp-(q-pos), l, r, q, prefix, ret);
            for (int k = 1; k <= q-pos; k++) {
                prefix.push_back(')');
                search(s, lp, rp-(q-pos)+k, l, r+k, q, prefix, ret);
            }
            for (int k = 1; k <= q-pos; k++) prefix.pop_back();
        } else {
            prefix.push_back(s[pos]);
            search(s, lp, rp, l, r, pos+1, prefix, ret);
            prefix.pop_back();
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
