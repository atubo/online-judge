#include <iostream>
using namespace std;

#define MOD 51123987

class Solution {
public:
    Solution() {
        setup();
    }

    int solve(const string& s) const {
        int n = s.length();
        int na = 0;
        int nb = 0;
        int nc = 0;
        
        char last = '\0';
        for (int i = 0; i < n; i++) {
            if (s[i] != last) {
                if (s[i] == 'a') na++;
                if (s[i] == 'b') nb++;
                if (s[i] == 'c') nc++;
                last = s[i];
            }
        }
        int64_t result;
        if (n % 3) {
            int n1, n2;
            if (n % 3 == 1) {
                n1 = n/3;
                n2 = n1 + 1;
            }
            else {
                n1 = n/3 + 1;
                n2 = n1 - 1;
            }
            result = dp[na][n1] * dp[nb][n1] % MOD * dp[nc][n2] % MOD +
                     dp[na][n1] * dp[nb][n2] % MOD * dp[nc][n1] % MOD +
                     dp[na][n2] * dp[nb][n1] % MOD * dp[nc][n1] % MOD;
        }
        else {
            result = dp[na][n/3] * dp[nb][n/3] % MOD * dp[nc][n/3] % MOD;
        }

        return result % MOD;
    }

private:
    static const int N = 151;
    void setup() {
        for (int i = 0; i < N; i++) {
            dp[i][0] = 1;
        }
        for (int i = 1; i < N; i++) {
            dp[0][i] = 0;
        }
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < N; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }

    int dp[N][N];
};

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    Solution solution;
    cout << solution.solve(s) << endl;

    return 0;
}
