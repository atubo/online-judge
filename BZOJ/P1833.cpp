// http://www.lydsy.com/JudgeOnline/problem.php?id=1833
// [ZJOI2010]count 数字计数

#include <inttypes.h>
#include <cstring>
#include <iostream>
using namespace std;

int64_t dp[14][10][10];
int digits[14];

int64_t dfs(int pos, int d, int x, int64_t a, int64_t f, bool bounded, bool leadingZero) {
    int64_t& dpEntry = dp[pos][d][x];
    if (!bounded && !leadingZero && dpEntry > -1) {
        return dpEntry;
    }

    bounded = bounded && (digits[pos] == d);
    leadingZero = leadingZero && (d == 0) && (pos != 0);

    if (pos == 0) {
        return d == x;
    }

    int maxd = (bounded ? digits[pos-1] : 9);
    int64_t ret = 0;
    for (int nextd = 0; nextd <= maxd; nextd++) {
        ret += dfs(pos-1, nextd, x, a, f/10, bounded, leadingZero);
    }
    if (d == x && !leadingZero) {
        ret += (bounded ? (a % f) + 1 : f);
    }

    if (!bounded && !leadingZero) {
        dpEntry = ret;
    }
    return ret;
}

int64_t solve(int64_t a, int x) {
    if (a == 0) return (x == 0);
    int n = 0;
    int64_t f = 1;
    int64_t b = a;

    while (a > 0) {
        digits[n++] = (a % 10);
        a /= 10;
        f *= 10;
    }

    int64_t ret = 0;
    for (int d = 0; d <= digits[n-1]; d++) {
        ret += dfs(n-1, d, x, b, f/10, true, d == 0);
    }
    return ret;
}

int64_t solve(int64_t a, int64_t b, int x) {
    if (a == 0) return solve(b, x);
    else return solve(b, x) - solve(a-1, x);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int64_t a, b;
    cin >> a >> b;
    for (int x = 0; x < 9; x++) {
        cout << solve(a, b, x) << " ";
    }
    cout << solve(a, b, 9) << endl;
    return 0;
}
