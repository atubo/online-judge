// https://leetcode.com/problems/strobogrammatic-number-iii/
// 248. Strobogrammatic Number III

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    vector<int> ONE = {0, 1, 8};
    vector<int> TWO = {0, 1, 6, 8, 9};
    vector<int> MATCH = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
public:
    int strobogrammaticInRange(string low, string high) {
        if (stol(low) > stol(high)) return 0;
        const int n = high.length();
        vector<int> dp0(n+1);
        solvedp(n, dp0);
        int ret = solve(high, dp0) - solve(low, dp0);
        ret += check(low);
        return ret;
    }

    void solvedp(int n, vector<int> &dp0) {
        dp0[0] = 0;
        dp0[1] = 2;
        for (int i = 2; i <= n; i++) {
            int tot = 1;
            for (int j = i-2; j >= 0; j -= 2) {
                tot += dp0[j];
            }
            dp0[i] = 4 * tot;
        }
    }


    int solve(const string &s, const vector<int> &dp0) {
        const int n = s.length();
        int ret = 1;
        for (int i = 1; i < n; i++) ret += dp0[i];
        vector<vector<int>> dp(n, vector<int>(n, -1));
        bool halfok = checkHalf(s);
        ret += solve(s, 0, n-1, true, 1, dp, halfok);
        return ret;
    }

    bool checkHalf(const string &s) {
        const int n = s.length();
        int x = s[(n-1)/2] - '0';
        if (n&1) {
            if (!(x == 0 || x == 1 || x == 8)) return true;
        }
        for (int k = (n-1)/2; k >= 0; k--) {
            x = s[k] - '0';
            if (!(x == 0 || x == 1 || x == 6 || x == 8 || x == 9)) return true;
            int y = s[n-1-k] - '0';
            if (y < MATCH[x]) return false;
            if (y > MATCH[x]) return true;
        }
        return true;
    }

    bool check(const string &s) {
        const int n = s.length();
        int l = 0, r = n-1;
        while (l <= r) {
            int x = s[l] - '0';
            int y = s[r] - '0';
            if (l < r) {
                if (!(x == 0 || x == 1 || x == 6 || x == 8 || x == 9)) {
                    return false;
                }
                if (y != MATCH[x]) return false;
            } else {
                if (!(x == 0 || x == 1 || x == 8)) return false;
            }
            l++;
            r--;
        }
        return true;
    }

    int solve(const string &s, int l, int r, bool bounded, int start,
              vector<vector<int>>& dp, bool halfok) {
        if (l > r) return (!bounded || halfok);
        if (dp[l][r] != -1 && !bounded) return dp[l][r];
        int ret = 0;
        int x = s[l] - '0';
        if (l == r) {
            for (int i = start; i < (int)ONE.size(); i++) {
                if (bounded && ONE[i] > x) break;
                ret += solve(s, l+1, r-1, bounded&&ONE[i]==x, 0, dp, halfok);
            }
            if (!bounded) dp[l][r] = ret;
            return ret;
        }
        for (int i = start; i < (int)TWO.size(); i++) {
            if (bounded && TWO[i] > x) break;
            ret += solve(s, l+1, r-1, bounded&&TWO[i]==x, 0, dp, halfok);
        }
        if (!bounded) dp[l][r] = ret;
        return ret;
    }
};

int main() {
    Solution solution;
    cout << solution.strobogrammaticInRange("0", "100") << endl;
    //cout << solution.solve("532") << endl;
    return 0;
}
