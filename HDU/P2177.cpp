// http://acm.hdu.edu.cn/showproblem.php?pid=2177
// 取(2堆)石子游戏

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;
const double f = (1 + sqrt(5)) / 2;

int solve(int b) {
    int lo = 0, hi = b;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (int((b - mid) * f) >= mid) lo = mid;
        else hi = mid;
    }
    if (int((b - lo) * f) == lo) return lo;
    else return -1;
}

PII solve(int a, int b) {
    int ap = solve(b);
    if (ap != -1) return make_pair(ap, b);
    ap = solve(a);
    return make_pair(ap, a);
}

int main() {
    int a, b;
    while (scanf("%d%d", &a, &b) && (a != 0 || b != 0)) {
        int ap = (b - a) * f;
        if (a == ap) {
            printf("0\n");
            continue;
        }
        printf("1\n");
        if (ap < a) {
            printf("%d %d\n", ap, b - a + ap);
        }
        int c, d;
        tie(c, d) = solve(a, b);
        printf("%d %d\n", c, d);
    }
    return 0;
}
