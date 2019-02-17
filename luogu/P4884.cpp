// https://www.luogu.org/problemnew/show/P4884
// 多少个1？

#include <bits/stdc++.h>
using namespace std;

const __int128_t ONE = 1;

namespace discrete_logarithm {
    int64_t pow(int64_t x, int64_t y, int64_t m) {
        int64_t ans = 1;
        while (y) {
            if (y & 1) ans = ONE * ans * x % m;
            x = ONE * x * x % m;
            y >>= 1;
        }
        return ans;
    }

    int64_t primeRoot(int64_t p) {
        vector<int64_t> factors;
        int64_t x = p - 1;
        for (int i = 2; ONE * i * i <= x; i++) {
            if (x % i == 0) {
                factors.push_back((p-1)/i);
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) factors.push_back((p-1)/x);

        for (int i = 2; ; i++) {
            bool ok = true;
            for (int64_t y: factors) {
                if (pow(i, y, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return i;
        }
        return -1;
    }


// (g, x, y) that a*x + b*y = g
void ext_gcd(__int128_t a, __int128_t b, __int128_t &g, __int128_t &x, __int128_t &y) {
    if (b == 0) {
        g = a; x = 1; y = 0;
        return;
    }
    __int128_t dp, xp, yp;
    ext_gcd(b, a % b, dp, xp, yp);
    g = dp;
    x = yp;
    y = xp - a / b * yp;
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int64_t n) {
    __int128_t d, xp, yp;
    ext_gcd(a, n, d, xp, yp);
    if (b % d == 0) {
        int64_t x0 = ((ONE * xp % n) * ((b / d) % n) % n + n) % n;
        return x0;
    } else {
        //abort();
        return -1;
    }
}

// returns x that alpha ^ x == beta mod prime
// alpha must be a primitive root
int64_t babystepGiantstep(int alpha, int64_t beta, int64_t prime) {
    const int64_t n = prime - 1;
    const int m = int(sqrt(n) + 1);
    unordered_map<int64_t, int> table;
    int64_t p = 1;
    for (int j = 0; j < m; j++) {
        table[p] = j;
        p = (ONE * p * alpha) % prime;
    }
    int64_t fac = mod_solve(p, 1, prime);
    int64_t gamma = beta;
    for (int i = 0; i < m; i++) {
        auto it = table.find(gamma);
        if (it != table.end()) {
            return (ONE * i * m + it->second) % n;
        }
        gamma = (ONE * gamma * fac) % prime;
    }
    return -1;
}
}

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int64_t K, P;

int main() {
    scanf("%ld%ld", &K, &P);
    int64_t beta = (K*9 + 1) % P;
    int64_t root = discrete_logarithm::primeRoot(P);
    int64_t m1 = discrete_logarithm::babystepGiantstep(root, beta, P);
    int64_t m2 = discrete_logarithm::babystepGiantstep(root, 10, P);
    int64_t g = gcd(m2, P-1);
    int64_t ans = discrete_logarithm::mod_solve(m2, m1, P-1);
    ans = ans % ((P-1)/g);
    printf("%ld", ans);
    return 0;
}
