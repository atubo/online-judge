// https://www.luogu.org/problem/show?pid=3172
// P3172 [CQOI2015]选数

#include <inttypes.h>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

const int64_t MOD = 1000000007;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int64_t sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t pwr(int64_t x, int64_t n) {
    if (n == 0) return 1;
    int64_t y = pwr(x, n/2);
    int64_t ans = mul(y, y);
    if (n & 1) ans = mul(ans, x);
    return ans;
}

int mu(int x) {
    if (x == 0) return 0;
    int ret = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            x /= i;
            ret = -ret;
            if (x % i == 0) return 0;
        }
    }
    if (x > 1) ret = -ret;
    return ret;
}

class Solution {
private:
    int N, K, L, H;
    vector<int> ps;
public:
    Solution() {
        cin >> N >> K >> L >> H;
    }

    void solve() {
        H = H / K;
        L = (L-1) / K;

        int64_t ans = 0;
        for (int i = 1; i <= H; i++) {
            int x = H/i - L/i;
            if (x == 0) {
                i = min(H/(H/i), L/i ? L/(L/i) : INT_MAX);
            } else {
                ans = add(ans, mul((mu(i) + MOD) % MOD, pwr(x, N)));
            }
        }
        cout << ans << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
