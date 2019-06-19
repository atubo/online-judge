// https://leetcode.com/problems/valid-palindrome-ii/
// 680. Valid Palindrome II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool validPalindrome(string s) {
        const int n = s.length();
        int p = 0, q = n-1;
        while (p < q && s[p] == s[q]) {
            p++;
            q--;
        }
        if (p >= q) return true;
        return check(s, p+1, q) || check(s, p, q-1);
    }

    bool check(const string &s, int p, int q) {
        while (p < q && s[p] == s[q]) {
            p++;
            q--;
        }
        return p >= q;
    }
};

int main() {
    Solution solution;
    return 0;
}
