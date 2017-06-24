// https://www.luogu.org/problem/show?pid=2431
// 正妹吃月饼

#include <bits/stdc++.h>
using namespace std;

int solve(int64_t a, int64_t b, int d) {
    if (d < 0) return 0;
    int d1 = (a >> d) & 1;
    int d2 = (b >> d) & 1;
    int64_t x = (a & (~(1LL << d)));
    int64_t y = (b & (~(1LL << d)));
    if (d1 && d2) return 1 + solve(x, y, d-1);
    else if (!d1 && d2) {
        return d + (y == ((1 << d) - 1));
    } else {
        assert(!d1 && !d2);
        return solve(x, y, d-1);
    }
}

int main() {
    int64_t a, b;
    cin >> a >> b;
    cout << solve(a, b, 63) << endl;
    return 0;
}
