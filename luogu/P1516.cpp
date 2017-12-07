// https://www.luogu.org/problemnew/show/1516
// 青蛙的约会

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

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    tie(d, xp, yp) = ext_gcd(a, n);
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int64_t X, Y, M, N, L;

int main() {
    cin >> X >> Y >> M >> N >> L;
    if (X < Y) {
        swap(X, Y);
        swap(M, N);
    }

    int64_t S = (L + N - M) % L;
    int64_t D = X - Y;
    if (D % gcd(S, L) != 0) {
        cout << "Impossible" << endl;
    } else {
        int64_t ans = mod_solve(S, D, L);
        ans = ans % (L / gcd(S, L));
        cout << ans << endl;
    }
    return 0;
}
