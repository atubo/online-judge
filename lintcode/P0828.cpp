#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool wordPattern(string &pattern, string &teststr) {
        vector<string> words = build(teststr);
        if (words.size() != pattern.length()) return false;
        map<string, char> toChar;
        map<char, string> toStr;
        for (int i = 0; i < (int)words.size(); i++) {
            auto w = words[i];
            char c = pattern[i];
            if (toChar.count(w) == 0 && toStr.count(c) == 0) {
                toChar[w] = c;
                toStr[c] = w;
            }
            if (!biinjection(toChar, toStr, w, c)) return false;
        }
        return true;
    }
private:
    vector<string> build(const string &s) {
        vector<string> ans;
        size_t p = 0;
        while (p < s.length()) {
            auto q = s.find_first_of(' ', p);
            if (q == string::npos) {
                ans.push_back(s.substr(p));
                break;
            } else {
                ans.push_back(s.substr(p, q-p));
                p = q+1;
            }
        }
        return ans;
    }

    bool biinjection(const map<string, char> &toChar,
                     const map<char, string> &toStr,
                     const string &w, char c) {
        return toChar.count(w) > 0 && toStr.count(c) > 0 &&
            toChar.at(w) == c && toStr.at(c) == w;
    }
};

int main() {
    Solution solution;
    return 0;
}
