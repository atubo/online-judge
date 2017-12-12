// https://www.luogu.org/problemnew/show/P1965
// 转圈游戏

#include <bits/stdc++.h>
using namespace std;

int64_t N, M, K, X;

int64_t pwr(int k, int n) {
    if (k == 0) return 1 % n;
    if (k == 1) return 10 % n;
    int64_t x = pwr(k/2, n);
    x = (x * x) % n;
    if (k & 1) x = (x * 10) % n;
    return x;
}

int64_t add(int64_t a, int64_t b) {
    return (a + b) % N;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % N;
}

int main() {
    scanf("%lld%lld%lld%lld", &N, &M, &K, &X);
    printf("%lld\n", add(X, mul(pwr(K, N), M)));
    return 0;
}
