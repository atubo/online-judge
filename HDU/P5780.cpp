// http://acm.hdu.edu.cn/showproblem.php?pid=5780
// gcd

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


class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, miu, phi;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        miu.resize(N+1);
        phi.resize(N+1);

        isPrime[0] = isPrime[1] = false;
        miu[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                miu[i] = -1;
                phi[i] = i - 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    miu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    break;
                } else {
                    miu[t] = -miu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                }
            }
        }
    }
};

const int MAXN = 1000000;

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

class Solution {
private:
    vector<int64_t> D;
    EulerSieve *sieve;
    int64_t inv_xm1;    // 1/(x-1)
public:
    Solution() {
        D.resize(MAXN+1);
        sieve = new EulerSieve(MAXN);

        buildD();
    }

    void buildD() {
        D[0] = -1;
        for (int i = 1; i <= MAXN; i++) {
            D[i] = add(D[i-1], 2 * sieve->phi[i]);
        }
    }

    int64_t solve(int64_t x, int64_t n) {
        if (x == 1) return 0;

        inv_xm1 = mod_solve(x-1, 1, MOD);
        int64_t ans = 0;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = n / (n/l);
            ans = add(ans, mul(D[n/l], sub(calcPs(x, r), calcPs(x, l-1))));
        }
        return ans;
    }

    int64_t calcPs(int x, int n) {
        // x^1 + x^2 + .. + x^n - n
        int64_t ans = pwr(x, n+1);
        ans = sub(ans, 1);
        ans = mul(ans, inv_xm1);
        ans = sub(ans, n+1);
        return ans;
    }
};

int main() {
    int T;
    cin >> T;
    Solution solution;
    for (int i = 0; i < T; i++) {
        int x, n;
        cin >> x >> n;
        cout << solution.solve(x, n) << endl;
    }
    return 0;
}
