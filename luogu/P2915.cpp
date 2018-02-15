// https://www.luogu.org/problemnew/show/P2915
// [USACO08NOV]奶牛混合起来Mixed Up Cows

#include <bits/stdc++.h>
using namespace std;

int N, K;
int S[16];
int64_t dp[1<<20];

int encode(int mask, int i) {
    return (i << 16) | mask;
}

void decode(int c, int &mask, int &i) {
    mask = c & (0xFFFF);
    i = (c >> 16);
}

int main() {
    scanf("%d%d", &N, &K);
    queue<int> q;
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
        int code = encode(1<<i, i);
        q.push(code);
        dp[code] = 1;
    }
    while (!q.empty()) {
        int code = q.front();
        q.pop();
        int64_t cnt = dp[code];
        int p, mask;
        decode(code, mask, p);
        for (int i = 0; i < N; i++) {
            if ((mask >> i) & 1 || abs(S[p] - S[i]) <= K) continue;
            code = encode(mask|(1<<i), i);
            if (!dp[code]) q.push(code);
            dp[code] += cnt;
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < N; i++) {
        int code = encode((1<<N)-1, i);
        ans += dp[code];
    }
    printf("%lld\n", ans);
    return 0;
}
