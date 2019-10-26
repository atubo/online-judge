// https://www.luogu.org/problem/P3266
// [JLOI2015]骗我呢

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000010;
const int P = 1000000007;
int C[MAXN], inv[MAXN];

int mul(int64_t a, int64_t b) {
    return (a * b) % P;
}

int add(int64_t a, int64_t b) {
    return (a + b) % P;
}

int sub(int64_t a, int64_t b) {
    return (a + P - b) % P;
}

int ceildiv(int a, int b) {
    if (a < b) return -(-a)/b;
    return a/b;
}

int main() {
    int l, n;
    scanf("%d%d", &l, &n);
    n++;
    int N = n + 2*l;
    inv[1] = 1;
    for (int i = 2; i <= N; i++) {
        inv[i] = mul(P-P/i, inv[P%i]);
    }
    C[0] = 1;
    for (int i = 1; i <= N; i++) {
        C[i] = mul(mul(C[i-1], N-i+1), inv[i]);
    }
    int ans = 0;
    for (int k = ceildiv(1-l, n+2); k <= (n+2+l)/(n+2); k++) {
        int p = k*(n+2) + l - 2;
        if (0 <= p && p <= N) ans = add(ans, C[p]);
        p = k*(n+2) + l - 1;
        if (0 <= p && p <= N) ans = sub(ans, C[p]);
    }
    printf("%d\n", ans);

    return 0;
}
