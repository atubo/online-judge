// https://leetcode.com/problems/decode-ways-ii/#/description
// 639. Decode Ways II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    static const int64_t MOD = 1000000007;

    int add(int64_t a, int64_t b) {
        return (a + b) % MOD;
    }
    int mul(int64_t a, int64_t b) {
        return (a * b) % MOD;
    }

    int toint(char cp, char cn) {
        return (cp - '0') * 10 + (cn - '0');
    }

public:
    int numDecodings(string s) {
        const int N = s.length();
        vector<int> dp(N+1);
        dp[0] = 1;
        dp[1] = (s[0] == '*' ? 9 : (s[0] != '0'));
        for (int n = 2; n <= N; n++) {
            char cn = s[n-1];
            char cp = s[n-2];
            if (cn != '*') {
                if (cn != '0') {
                    dp[n] = dp[n-1];
                    if (cp != '*') {
                        int x = toint(cp, cn);
                        if (10 <= x && x <= 26) {
                            dp[n] = add(dp[n], dp[n-2]);
                        }
                    } else {
                        dp[n] = add(dp[n], dp[n-2]);
                        if (cn <= '6') dp[n] = add(dp[n], dp[n-2]);
                    }
                } else {
                    if (cp == '*') {
                        dp[n] = add(dp[n-2], dp[n-2]);
                    } else {
                        if (cp == '1' || cp == '2') {
                            dp[n] = dp[n-2];
                        } else {
                            dp[n] = 0;
                        }
                    }
                }
            } else {
                dp[n] = mul(dp[n-1], 9);
                if (cp != '*') {
                    if (cp == '1') {
                        dp[n] = add(dp[n], mul(dp[n-2], 9));
                    } else if (cp == '2') {
                        dp[n] = add(dp[n], mul(dp[n-2], 6));
                    }
                } else {
                    dp[n] = add(dp[n], mul(dp[n-2], 15));
                }
            }
        }
        return dp[N];
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    cout << solution.numDecodings(s) << endl;
    return 0;
}
