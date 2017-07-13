// https://leetcode.com/problems/isomorphic-strings/#/description
// 205. Isomorphic Strings

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        map<char, char> fwd, bwd;
        for (int i = 0; i < (int)s.length(); i++) {
            char cs = s[i], ct = t[i];
            if (fwd.count(cs) == 0 && bwd.count(ct) == 0) {
                fwd[cs] = ct;
                bwd[ct] = cs;
            } else if (fwd.count(cs) == 1 && bwd.count(ct) == 1 &&
                       fwd[cs] == ct && bwd[ct] == cs) {
                continue;
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    string s, t;
    cin >> s >> t;
    Solution solution;
    cout << solution.isIsomorphic(s, t) << endl;
    return 0;
}
