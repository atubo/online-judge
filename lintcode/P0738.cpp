// https://www.lintcode.com/problem/count-different-palindromic-subsequences/description
// 738. Count Different Palindromic Subsequences

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const int MOD = 1e9 + 7;

    int add(int64_t a, int64_t b) {
        return (a + b) % MOD;
    }

    int sub(int64_t a, int64_t b) {
        return (a - b + MOD) % MOD;
    }

    int solve(int p, int q, const string &s, vector<vector<int>> &dp) {
        if (dp[p][q] >= 0) return dp[p][q];
        int &ret = dp[p][q];
        if (q - p <= 0) return ret = q-p+1;
        if (s[p] == s[q]) {
            int l = p+1, r = q-1;
            while (s[l] != s[p]) l++;
            while (s[r] != s[q]) r--;
            if (l == r) {
                ret = add(2*solve(p+1, q-1, s, dp), 1);
            } else if (l < r) {
                ret = sub(2*solve(p+1, q-1, s, dp), solve(l+1, r-1, s, dp));
            } else {
                ret = add(2*solve(p+1, q-1, s, dp), 2);
            }
        } else {
            ret = solve(p+1, q, s, dp);
            ret = add(ret, solve(p, q-1, s, dp));
            ret = sub(ret, solve(p+1, q-1, s, dp));
        }
        return ret;
    }

    int countPalindSubseq(string &str) {
        const int n = str.length();
        if (n == 0) return 0;
        vector<vector<int>> dp(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(n, -1);
        }
        return solve(0, n-1, str, dp);
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    cout << solution.countPalindSubseq(s) << endl;
    return 0;
}


