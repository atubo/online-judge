// https://leetcode.com/problems/find-the-closest-palindrome/
// 564. Find the Closest Palindrome

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string nearestPalindromic(string n) {
        const int m = n.length();
        vector<int64_t> P10(m+1);
        P10[0] = 1;
        for (int i = 1; i <= m; i++) P10[i] = P10[i-1]*10;

        int64_t x = stol(n);
        if (m == 1) return to_string(x == 0 ? 1 : x-1);
        vector<int64_t> c;
        int64_t t;
        if ((t = P10[m]+1) != x) c.push_back(t);
        if ((t = P10[m-1]-1) != x) c.push_back(t);
        int64_t mi = mirror(n);
        if (mi != x) c.push_back(mi);
        if ((t = minus1(mi)) != x) c.push_back(t);
        if ((t = plus1(mi)) != x) c.push_back(t);
        int64_t d = abs(c[0] - x);
        int id = 0;
        for (int i = 1; i < (int)c.size(); i++) {
            if ((x != c[i]) &&
                (abs(c[i]-x) < d || (abs(c[i]-x) == d && c[i] < c[id]))) {
                d = abs(c[i]-x);
                id = i;
            }
        }
        return to_string(c[id]);
    }

    int64_t mirror(const string &s) {
        string t = s;
        int p = 0, q = s.length()-1;
        while (p < q) {
            t[q--] = t[p++];
        }
        return stol(t);
    }

    int64_t minus1(int64_t c) {
        string t = to_string(c);
        const int n = t.length();
        t[(n-1)/2] = (t[(n-1)/2] == '0' ? '0' : t[(n-1)/2]-1);
        if ((n & 1) == 0)t[n/2] = (t[n/2] == '0' ? '0' : t[n/2]-1);
        return stol(t);
    }

    int64_t plus1(int64_t c) {
        string t = to_string(c);
        const int n = t.length();
        t[(n-1)/2] = (t[(n-1)/2] == '9' ? '9' : t[(n-1)/2]+1);
        if ((n & 1) == 0) t[n/2] = (t[n/2] == '9' ? '9' : t[n/2]+1);
        return stol(t);
    }
};

int main() {
    Solution solution;
    cout << solution.nearestPalindromic("11911");
    return 0;
}
