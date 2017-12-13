// https://www.luogu.org/problemnew/show/1062
// 数列

#include <bits/stdc++.h>
using namespace std;

int K, N;

int64_t pwr(int k, int n) {
    int64_t ret = 1;
    for (int i = 0; i < n; i++) {
        ret *= k;
    }
    return ret;
}

int main() {
    scanf("%d%d", &K, &N);
    int64_t ret = 0;

    for (int i = 11; i >= 0; i--) {
        if (N & (1 << i)) {
            ret += pwr(K, i);
        }
    }
    printf("%lld\n", ret);
    return 0;
}
