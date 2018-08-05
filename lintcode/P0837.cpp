// https://www.lintcode.com/problem/palindromic-substrings/description
// 837. Palindromic Substrings

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int countPalindromicSubstrings(string &str) {
        const int n = str.length();
        int ans = n;
        for (int i = 0; i < n; i++) {
            for (int k = 1; i-k >= 0 && i+k < n; k++) {
                if (str[i-k] != str[i+k]) break;
                ans++;
            }
        }
        for (int i = 0; i < n-1; i++) {
            for (int k = 1; i+1-k >= 0 && i+k < n; k++) {
                if (str[i+1-k] != str[i+k]) break;
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    string s;
    cin >> s;
    cout << solution.countPalindromicSubstrings(s) << endl;
    return 0;
}
