// https://leetcode.com/problems/longest-repeating-character-replacement/#/description
// 424. Longest Repeating Character Replacement

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        int ret = 0;
        for (char c = 'A'; c <= 'Z'; c++) {
            ret = max(ret, solve(s, c, k));
        }
        return ret;
    }

    int solve(const string& s, char c, int k) {
        const int N = s.length();
        int ret = 0;
        int p = 0, q = 0, cnt = 0;
        while (true) {
            while (q < N && cnt <= k) {
                ret = max(ret, q-p);
                cnt += (s[q++] != c);
            }
            if (cnt <= k) {
                ret = max(ret, q-p);
                break;
            }
            while (cnt > k) {
                cnt -= (s[p++] != c);
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    string s;
    int k;
    cin >> s >> k;
    cout << solution.characterReplacement(s, k) << endl;
    return 0;
}
