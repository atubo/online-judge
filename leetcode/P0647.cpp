// https://leetcode.com/problems/palindromic-substrings/
// 647. Palindromic Substrings

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int countSubstrings(string s) {
        const int n = s.length();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            ret += count1(s, i);
        }
        for (int i = 0; i < n-1; i++) {
            ret += count2(s, i);
        }
        return ret;
    }

    int count1(const string &s, int c) {
        const int n = s.length();
        int maxl = min(c, n-1-c);
        for (int l = 1; l <= maxl; l++) {
            if (s[c-l] != s[c+l]) return l;
        }
        return maxl + 1;
    }

    int count2(const string &s, int c) {
        const int n = s.length();
        int maxl = min(c+1, n-1-c);
        for (int l = 1; l <= maxl; l++) {
            if (s[c-l+1] != s[c+l]) return l-1;
        }
        return maxl;
    }
};

int main() {
    Solution solution;
    return 0;
}
