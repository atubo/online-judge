// https://leetcode.com/problems/group-shifted-strings/
// 249. Group Shifted Strings

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        map<string, vector<string>> m;
        for (const string &s: strings) {
            string cs = canon(s);
            m[cs].push_back(s);
        }
        vector<vector<string>> ret;
        for (auto it = m.begin(); it != m.end(); ++it) {
            ret.push_back(it->second);
        }
        return ret;
    }

    string canon(const string &s) {
        const int n = s.length();
        string t(n, '\0');
        int d = s[0] - 'a';
        t[0] = 'a';
        for (int i = 1; i < n; i++) {
            char c = s[i] - d;
            if (c < 'a') c += 26;
            t[i] = c;
        }
        return t;
    }
};

int main() {
    Solution solution;
    return 0;
}
