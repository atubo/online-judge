// https://leetcode.com/problems/valid-word-abbreviation/
// 408. Valid Word Abbreviation

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        const int m = word.length(), n = abbr.length();
        int p = 0, q = 0;
        while (p < m && q < n) {
            if (isdigit(abbr[q])) {
                if (abbr[q] == '0') return false;
                int x, e;
                tie(x, e) = parseInt(abbr, q);
                p += x;
                q = e;
            } else {
                if (word[p] != abbr[q]) return false;
                p++;
                q++;
            }
        }
        return p == m && q == n;
    }
private:
    pair<int, int> parseInt(const string &s, int p) {
        const int n = s.length();
        int ret = 0;
        int q = p;
        while (q < n && isdigit(s[q])) {
            ret = ret*10 + s[q] - '0';
            q++;
        }
        return make_pair(ret, q);
    }
};

int main() {
    Solution solution;
    return 0;
}
