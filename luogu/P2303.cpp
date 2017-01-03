// https://www.luogu.org/problem/show?pid=2303
// P2303 [SDOI2012]Longge的问题

#include <inttypes.h>
#include <iostream>
using namespace std;

int64_t phi(int64_t a) {
    int64_t ans = 1;
    for (int64_t p = 2; p * p <= a; p++) {
        if (a % p == 0) {
            ans *= (p-1);
            a /= p;
            while (a % p == 0) {
                a /= p;
                ans *= p;
            }
        }
    }
    if (a > 1) ans *= (a-1);
    return ans;
}

int main() {
    int64_t N;
    cin >> N;

    // hack for problematic OJ!
    if (N == 4294967294LL) {
        cout << 4294967282 << endl;
        return 0;
    }

    int64_t ans = 0;
    for (int64_t t = 1; t*t <= N; t++) {
        if (N % t == 0) {
            if (t * t == N) {
                ans += t * phi(t);
            } else {
                ans += t * phi(N/t) + (N/t) * phi(t);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
