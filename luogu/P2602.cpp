// https://www.luogu.org/problemnew/show/P2602
// [ZJOI2010]数字计数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
int64_t dp[10][MAXN];
int s[MAXN];

int64_t tail(int depth) {
    int64_t ret = 0;
    if (depth == -1) return ret;
    for (int i = depth; i >= 0; i--) {
        ret = ret * 10 + s[i];
    }
    return ret;
}

int64_t pow_of_ten[MAXN];

int64_t solve(bool clamp, int depth, int digit) {
    if (depth == -1) return 0;
    if (!clamp && dp[digit][depth] >= 0) return dp[digit][depth];
    int64_t ret = 0;
    if (clamp) {
        for (int i = 0; i < s[depth]; i++) {
            ret += solve(false, depth-1, digit);
        }
        ret += solve(true, depth-1, digit);
    } else {
        ret = 10LL * solve(false, depth-1, digit);
    }
    if (!clamp || digit < s[depth]) {
        ret += pow_of_ten[depth];
    } else if (digit == s[depth]) {
        ret += tail(depth-1) + 1;
    }
    if (!clamp) dp[digit][depth] = ret;
    return ret;
}

int64_t A, B;

vector<int64_t> solveOneCase(int64_t x) {
    memset(dp, -1, sizeof(dp));
    vector<int64_t> ret(10, 0);
    ret[0] = 1;
    if (x == 0) return ret;
    int i = 0;
    while (x > 0) {
        s[i] = x % 10;
        x /= 10;
        i++;
    }
    for (int digit = 0; digit < 10; digit++) {
        ret[digit] += solve(true, i-1, digit);
    }
    for (int j = 0; j < i; j++) {
        ret[0] -= pow_of_ten[j];
    }
    return ret;
}

int main() {
    pow_of_ten[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow_of_ten[i] = pow_of_ten[i-1] * 10;
    }
    scanf("%ld%ld", &A, &B);
    auto sa = solveOneCase(A-1);
    auto sb = solveOneCase(B);
    for (int i = 0; i < 10; i++) {
        printf("%ld ", sb[i] - sa[i]);
    }
    printf("\n");
    return 0;
}
