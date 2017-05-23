// https://www.luogu.org/problem/show?pid=2520
// [HAOI2011]向量

#include <bits/stdc++.h>
using namespace std;

// (g, x, y) that a*x + b*y = g
tuple<int64_t, int64_t, int64_t> ext_gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    }
    int64_t dp, xp, yp;
    tie(dp, xp, yp) = ext_gcd(b, a % b);
    return make_tuple(dp, yp, xp - a / b * yp);
}

bool solve(int a, int b, int x, int y) {
    if (a == 0 && b == 0) {
        return (x == 0 && y == 0);
    }
    if (a == 0 || b == 0) {
        return (x % (a + b) == 0) && (y % (a + b) == 0);
    }

    int64_t g, u, v, u1, v1, u2, v2;
    tie(g, u, v) = ext_gcd(a, b);
    if (x % g != 0 || y % g != 0) {
        return false;
    }
    u1 = u * x / g;
    v1 = v * x / g;
    u2 = u * y / g;
    v2 = v * y / g;
    int64_t a2 = a / g;
    int64_t b2 = b / g;

    return ((u1 + v2 + a2 + b2) % 2 == 0) && ((u2 + v1 + a2 + b2) % 2 == 0);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int a, b, x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);
        bool ok = solve(a, b, x, y) || solve(a, b, x+a, y+b) ||
            solve(a, b, x+b, y+a) || solve(a, b, x+a+b, y+a+b);
        printf(ok ? "Y\n" : "N\n");
    }
    return 0;
}
