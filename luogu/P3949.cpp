// https://www.luogu.org/problemnew/show/P3949
// 答案错误

#include <bits/stdc++.h>
using namespace std;

int N, Q;

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < Q; i++) {
        int64_t x;
        scanf("%ld", &x);
        int ret = 1;
        for (int d = N-1; d >= 0; d--) {
            if (x > (1LL << d)) {
                x -= (1LL << d);
                ret = -ret;
            }
        }
        printf(ret == 1 ? "X\n" : "Z\n");
    }
    return 0;
}
