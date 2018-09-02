// https://www.luogu.org/problemnew/show/P1582
// 倒水

#include <bits/stdc++.h>
using namespace std;

int64_t N, K;

int solve() {
    int popcount = __builtin_popcount(N);
    int64_t r = 0, n = N;
    while (r < popcount-K) {
        int x = ((n ^ (n+1)) + 1) >> 1;
        int t = __builtin_ctz(x);
        if (r + t - 1 < popcount - K) {
            n = (n | x);
            r--;
        } else {
            n = (n | x) & (~(x-1));
            r += t - 1;
        }
    }
    return n - N;
}
    

int main() {
    scanf("%ld%ld", &N, &K);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
