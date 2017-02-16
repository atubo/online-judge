// http://poj.org/problem?id=3252
// Round Numbers

#include <cstring>
#include <iostream>
using namespace std;

int dp[68][34][2];
int digits[34];

int dfs(int ndiff, int pos, int d, bool bounded, bool leadingZero) {
    int& dpEntry = dp[ndiff+32][pos][d];
    if (!bounded && !leadingZero && dpEntry != -1) return dpEntry;

    bounded = bounded && digits[pos] == d;
    leadingZero = leadingZero && (d == 0);
    if (leadingZero) ndiff = 0;
    else ndiff += (d == 0 ? 1 : -1);
    if (pos == 0) return ndiff >= 0;
    int maxd = (bounded ? digits[pos-1] : 1);
    int ret = 0;
    for (int nextd = 0; nextd <= maxd; nextd++) {
        ret += dfs(ndiff, pos-1, nextd, bounded, leadingZero);
    }
    if (!bounded && !leadingZero) {
        dpEntry = ret;
    }
    return ret;
}

int solve(int a) {
    if (a == 0) return 1;
    int n = 0;
    while (a > 0) {
        digits[n++] = (a & 1);
        a = (a >> 1);
    }

    int ret = 0;
    for (int d = 0; d < 2; d++) {
        ret += dfs(0, n-1, d, true, d == 0);
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    int a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a-1) << endl;
    return 0;
}
