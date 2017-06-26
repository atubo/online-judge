// https://leetcode.com/problems/unique-substrings-in-wraparound-string/#/description
// 467. Unique Substrings in Wraparound String
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findSubstringInWraproundString(string p) {
        const int N = p.length();
        if (N == 0) return 0;
        vector<int> dp(N);
        dp[0] = 1;
        for (int i = 1; i < N; i++) {
            if (p[i] == 'a' + (p[i-1] - 'a' + 1) % 26) {
                dp[i] = dp[i-1] + 1;
            } else {
                dp[i] = 1;
            }
        }
        vector<int> cnt(26);
        for (int i = 0; i < N; i++) {
            char c = p[i];
            cnt[c-'a'] = max(cnt[c-'a'], dp[i]);
        }
        return accumulate(cnt.begin(), cnt.end(), 0);
    }
};

int main() {
    Solution solution;
    string s;
    cin >> s;
    cout << solution.findSubstringInWraproundString(s) << endl;
    return 0;
}
