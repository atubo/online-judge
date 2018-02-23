// https://www.luogu.org/problemnew/show/P1961
// 最轻的天平_NOI导刊2009普及（6）

#include <bits/stdc++.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

const int MAXN = 110;
struct Balance {
    int P, Q, R, B;
} balance[MAXN];

int N;
bool isChild[MAXN];

int64_t solve(int node) {
    if (node == 0) return 1;
    int64_t lw = solve(balance[node].R);
    int64_t rw = solve(balance[node].B);
    int64_t gw = gcd(lw, rw);
    int64_t lwp = lw/gw, rwp = rw/gw;

    int64_t p = balance[node].P, q = balance[node].Q;
    int64_t gl = gcd(p, q);
    p /= gl;
    q /= gl;
    int64_t g0 = gcd(rwp * q, lwp * p);
    return (lw * rwp * q + rw * lwp * p) / g0;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int p, q, r, b;
        scanf("%d%d%d%d", &p, &q, &r, &b);
        balance[i] = {p, q, r, b};
        isChild[r] = isChild[b] = true;
    }
    int root = 0;
    for (; root <= N; root++) {
        if (!isChild[root]) break;
    }
    int64_t ans = solve(root);
    printf("%lld\n", ans);
    return 0;
}
