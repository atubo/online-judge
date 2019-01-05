// https://www.luogu.org/problemnew/show/P3166
// [CQOI2014]数三角形

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int N, M;
int main() {
    scanf("%d%d", &N, &M);
    N++; M++;
    int64_t n = N * M;
    int64_t ans = n*(n+1)*(n+2)/6;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int c = gcd(i, j) + 1;
            int64_t f = (i > 0 && j > 0) ? 2 : 1;
            ans -= f *(N-i)*(M-j)*c;
        }
    }
    printf("%ld\n", ans);
    return 0;
}
