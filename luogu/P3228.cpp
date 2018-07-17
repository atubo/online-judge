// https://www.luogu.org/problemnew/show/P3228
// [HNOI2013]数列

#include <bits/stdc++.h>
using namespace std;

int64_t N, K, M, P;

int64_t fastPower(int64_t x, int64_t n) {
    if (n == 0) return 1;
    int64_t y = fastPower(x, n/2);
    y = (y * y) % P;
    if (n & 1) y = (y * x) % P;
    return y;
}

int64_t add(int64_t a, int64_t b) {
    return (a + b) % P;
}

int64_t sub(int64_t a, int64_t b) {
    return (a + P - b) % P;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % P;
}

int main() {
    scanf("%lld%lld%lld%lld", &N, &K, &M, &P);
    if (K == 1) {
        printf("%lld\n", N);
        return 0;
    }
    int64_t mp = fastPower(M, K-1);
    int64_t ans = mul((N-M*(K-1)) % P, mp);
    mp = fastPower(M, K-2);
    ans = add(ans, mul(mul(mp, K-1), (M*(M-1)/2)%P));
    printf("%lld\n", ans);
    return 0;
}
