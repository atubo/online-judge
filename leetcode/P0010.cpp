// 10. Regular Expression Matching
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        return match(s, p, 0, 0);
    }

    bool match(const string& str, const string& pat, int p, int q) {
        int M = str.length();
        int N = pat.length();
        if (p == M) return isNullable(pat, q);
        if (q == N) return false;

        if (q < N-1 && pat[q+1] == '*') {
            if (match(str, pat, p, q+2)) return true;
            for (; p < M && matchChar(str[p], pat[q]); p++) {
                if (match(str, pat, p+1, q+2)) return true;
            }
            return false;
        } else {
            return matchChar(str[p], pat[q]) && match(str, pat, p+1, q+1);
        }
    }

    bool isNullable(const string& pat, int p) {
        int N = pat.length();
        if (p == N) return true;
        if (p < N-1 && pat[p+1] == '*') return isNullable(pat, p+2);
        return false;
    }

    bool matchChar(char s, char p) {
        return p == '.' || p == s;
    }
};

int main() {
    Solution solution;
    string s, p;
    cin >> s >> p;
    cout << solution.isMatch(s, p) << endl;
    return 0;
}
