// https://www.lintcode.com/problem/minimum-window-substring/description?_from=ladder&&fromId=23
// 32. Minimum Window Substring

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string minWindow(string &source, string &target) {
        string ret;
        if (target.empty()) return ret;
        map<char, int> req;
        for (char c: target) {
            req[c]++;
        }
        map<char, int> cnt;
        const int n = source.length();
        int missing = req.size();
        int p = 0, q = 0;
        while (q < n) {
            while (missing > 0 && q < n) {
                push(source, p, q++, req, cnt, missing, ret);
            }
            while (missing == 0) {
                pop(source, p++, q, req, cnt, missing, ret);
            }
        }
        return ret;
    }

    void push(const string &source, int p, int q, const map<char, int>& req,
              map<char, int> &cnt, int &missing, string &ret) {
        char c = source[q];
        if (req.count(c) == 0) return;
        cnt[c]++;
        if (cnt[c] == req.at(c)) missing--;
        if (missing == 0) {
            if (ret.empty() || q-p+1 < (int)ret.length()) {
                ret = source.substr(p, q-p+1);
            }
        }
    }

    void pop(const string &source, int p, int q, const map<char, int>& req,
             map<char, int> &cnt, int &missing, string &ret) {
        char c = source[p];
        if (req.count(c) > 0) {
            cnt[c]--;
            if (cnt[c] == req.at(c)-1) missing++;
        }
        if (missing == 0) {
            if (q-p-1 < (int)ret.length()) {
                ret = source.substr(p+1, q-p-1);
            }
        }
    }
};

int main() {
    Solution solution;
    string s1, s2;
    cin >> s1 >> s2;
    cout << solution.minWindow(s1, s2) << endl;
    return 0;
}
