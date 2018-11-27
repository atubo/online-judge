// https://leetcode.com/problems/one-edit-distance/
// 161. One Edit Distance

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (s.length() < t.length()) swap(s, t);
        int l1 = s.length();
        int l2 = t.length();
        if (l1-l2 > 1) return false;
        int p = 0;
        while (p < l1 && s[p] == t[p]) p++;
        if (p == l1) return false;
        for (int i = p+1; i < l1; i++) {
            if (s[i] != t[i+l2-l1]) return false;
        }
        return true;
    }
};

int main() {
    string s, t;
    cin >> s >> t;
    Solution solution;
    cout << solution.isOneEditDistance(s, t) << endl;
    return 0;
}
