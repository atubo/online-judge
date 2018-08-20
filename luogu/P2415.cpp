// https://www.luogu.org/problemnew/show/P2415
// 集合求和

#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, cnt = 0;
    int64_t s = 0;
    while (scanf("%d", &x) == 1) {
        s += x;
        cnt++;
    }
    printf("%ld\n", (s << (cnt-1)));
    return 0;
}
