// https://leetcode.com/problems/number-of-atoms/
// 726. Number of Atoms

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string countOfAtoms(string formula) {
        const int n = formula.length();
        map<string, int> cnt = parse(formula, 0, n-1);
        return convert(cnt);
    }

    string convert(const map<string, int> &cnt) {
        string ret;
        for (auto it = cnt.begin(); it != cnt.end(); ++it) {
            string t = it->first;
            int x = it->second;
            ret += t;
            if (x > 1) ret += to_string(x);
        }
        return ret;
    }

    map<string, int> merge(const map<string, int> &cnt1,
                           const map<string, int> &cnt2) {
        set<string> keys;
        for (auto it = cnt1.begin(); it != cnt1.end(); ++it) {
            keys.insert(it->first);
        }
        for (auto it = cnt2.begin(); it != cnt2.end(); ++it) {
            keys.insert(it->first);
        }

        map<string, int> cnt;
        for (const string &key: keys) {
            int x = 0;
            if (cnt1.find(key) != cnt1.end()) x += cnt1.at(key);
            if (cnt2.find(key) != cnt2.end()) x += cnt2.at(key);
            cnt[key] = x;
        }
        return cnt;
    }

    map<string, int> parse(const string &formula, int l, int r) {
        if (l > r) return map<string, int>();
        if (formula[l] == '(') {
            int rp = findRightParenthese(formula, l);
            int nxt = findFirstNotDigit(formula, rp+1, r);
            auto cnt1 = parse(formula, l+1, rp-1);
            if (nxt > rp+1) {
                int x = stoi(formula.substr(rp+1, nxt-rp-1));
                for (auto it = cnt1.begin(); it != cnt1.end(); ++it) {
                    it->second *= x;
                }
            }
            auto cnt2 = parse(formula, nxt, r);
            return merge(cnt1, cnt2);
        } else {
            int nxt = findFirstElement(formula, l+1, r);
            auto cnt1 = parseElement(formula.substr(l, nxt-l));
            auto cnt2 = parse(formula, nxt, r);
            return merge(cnt1, cnt2);
        }
    }

    int findRightParenthese(const string &s, int l) {
        assert(s[l] == '(');
        int lp = 1;
        for (int i = l+1; true; i++) {
            if (s[i] == '(') lp++;
            if (s[i] == ')') lp--;
            if (lp == 0) return i;
        }
        return -1;
    }

    int findFirstNotDigit(const string &s, int p, int r) {
        while (p <= r && isdigit(s[p])) p++;
        return p;
    }

    int findFirstElement(const string &s, int p, int r) {
        while (p <= r && !(s[p] == '(' || isupper(s[p]))) p++;
        return p;
    }

    map<string, int> parseElement(const string &s) {
        const int n = s.length();
        int p = 0;
        while (p < n && !isdigit(s[p])) p++;
        string elem = s.substr(0, p);
        int cnt = 1;
        if (p != n) cnt = stoi(s.substr(p, n-p));
        map<string, int> ret;
        ret[elem] = cnt;
        return ret;
    }
};

int main() {
    Solution solution;
    cout << solution.countOfAtoms("(OH)2") << endl;
    return 0;
}
