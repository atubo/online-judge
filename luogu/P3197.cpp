// https://www.luogu.org/problem/show?pid=3197
// [HNOI2008]越狱

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100003;

int sub(int a, int b) {
    return (a + MOD - b) % MOD;
}

int mul(int a, int b) {
    return (int64_t(a) * b ) % MOD;
}

int power(int a, int64_t n) {
    if (n == 0) return 1;
    if (n == 1) return a;
    int x = power(a, n/2);
    int ret = mul(x, x);
    if (n & 1) ret = mul(ret, a);
    return ret;
}

int main() {
    int M;
    int64_t N;
    scanf("%d %lld", &M, &N);
    M = M % MOD;
    printf("%d\n", sub(power(M, N), mul(power(sub(M, 1), N-1), M)));
    return 0;
}
