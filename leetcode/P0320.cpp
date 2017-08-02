// https://leetcode.com/problems/generalized-abbreviation/description/
// 320. Generalized Abbreviation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        const int N = word.length();
        vector<vector<string>> dp(N+1);
        dp[N] = {""};
        for (int i = N-1; i >= 0; i--) {
            for (const string& suffix: dp[i+1]) {
                dp[i].push_back(word[i] + suffix);
            }
            for (int j = i+1; j < N; j++) {
                for (const string& suffix: dp[j+1]) {
                    dp[i].push_back(to_string(j-i) + word[j] + suffix);
                }
            }
            dp[i].push_back(to_string(N-i));
        }
        return dp[0];
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    auto ret = solution.generateAbbreviations(s);
    for (auto abbr: ret) {
        cout << abbr << endl;
    }
    return 0;
}
