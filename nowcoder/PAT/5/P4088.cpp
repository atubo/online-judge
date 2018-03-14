// https://www.nowcoder.com/pat/5/problem/4088
// Counting Ones (30)

#include <bits/stdc++.h>
using namespace std;

int calcDmax(int n) {
    int x = 1, ret = 0;
    while (x <= n) {
        ret++;
        x *= 10;
    }
    return ret;
}

void populateDigits(int n, int *digits, int dmax) {
    for (int i = 0; i <= dmax; i++) {
        digits[i] = n % 10;
        n = n / 10;
    }
}

int N;
map<pair<int, bool>, int> dp;

int solve(int d, int *digits, bool bounded) {
    if (d < 0) return 0;
    pair<int, bool> key = make_pair(d, bounded);
    if (dp.find(key) != dp.end()) {
        return dp[key];
    }
    int &ret = dp[key] = 0;
    int P10 = 1;
    for (int i = 0; i < d; i++) P10 *= 10;

    if (bounded) {
        ret += digits[d] * solve(d-1, digits, false);
        if (digits[d] == 1) ret += (N % P10 + 1);
        if (digits[d] > 1) {
            ret += P10;
        }
        ret += solve(d-1, digits, true);
    } else {
        ret = 10 * solve(d-1, digits, false) + P10;
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    int dmax = calcDmax(N);
    int digits[dmax+1];
    populateDigits(N, digits, dmax);
    int ret = solve(dmax, digits, true);
    printf("%d\n", ret);
    return 0;
}
