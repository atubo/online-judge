// https://www.lintcode.com/problem/permutation-in-string/description
// 1169. Permutation in String

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool checkInclusion(string &s1, string &s2) {
        const int m = s1.length();
        int pattern[256] = {0};
        int missing = 0;
        for (char c: s1) {
            pattern[c]++;
            if (pattern[c] == 1) missing++;
        }
        int cnt[256] = {0};
        int p = 0, q = 0;
        const int n = s2.length();
        while (true) {
            while (q < n && missing) {
                char c = s2[q];
                if (++cnt[c] == pattern[c]) missing--;
                q++;
            }
            if (q == n && missing) break;
            while (missing == 0) {
                if (q - p == m) return true;
                char c = s2[p];
                if (cnt[c]-- == pattern[c]) missing++;
                p++;
            }
        }

        return false;
    }
};

int main() {
    Solution solution;
    string s1;
    string s2;
    cin >> s1 >> s2;
    cout << solution.checkInclusion(s1, s2) << endl;
    return 0;
}
