// https://www.lintcode.com/problem/isomorphic-strings/description
// 638. Isomorphic Strings

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string &s, string &t) {
        int m1[128], m2[128];
        memset(m1, -1, sizeof(m1));
        memset(m2, -1, sizeof(m2));
        for (int i = 0; i < (int)s.length(); i++) {
            char c1 = s[i], c2 = t[i];
            if (m1[c1] == -1 && m2[c2] == -1) {
                m1[c1] = c2;
                m2[c2] = c1;
            } else {
                if (m1[c1] != c2) return false;
            }
        }
        return true;
    }
};

int main() {
    Solution solution;
    string s, t;
    cin >> s >> t;
    cout << solution.isIsomorphic(s, t) << endl;
    return 0;
}
