// https://www.luogu.org/problemnew/show/P2651
// 添加括号III

#include <bits/stdc++.h>
using namespace std;


int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int T;

int main() {
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int64_t a, b;
        scanf("%lld%lld", &a, &b);
        int64_t g = gcd(a, b);
        b /= g;
        for (int i = 2; i < n; i++) {
            scanf("%lld", &a);
            g = gcd(a, b);
            b /= g;
        }
        if (b == 1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
