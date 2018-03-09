// https://www.luogu.org/problemnew/show/P1218
// [USACO1.5]特殊的质数肋骨 Superprime Rib

#include <bits/stdc++.h>
using namespace std;

bool isPrime(int x) {
    for (int i = 3; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> sp(9);
    sp[1] = {2, 3, 5, 7};
    for (int i = 2; i <= n; i++) {
        for (int prefix: sp[i-1]) {
            for (int d = 1; d < 10; d += 2) {
                int x = prefix * 10 + d;
                if (isPrime(x)) {
                    sp[i].push_back(x);
                }
            }
        }
    }
    for (int x: sp[n]) {
        printf("%d\n", x);
    }
    return 0;
}
