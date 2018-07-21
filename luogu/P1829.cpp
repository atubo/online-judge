// https://www.luogu.org/problemnew/show/P1829
// [国家集训队]Crash的数字表格 / JZPTAB

#include <bits/stdc++.h>
using namespace std;

const int MOD = 20101009;

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
    return (a + MOD - (b%MOD)) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, f;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        f.resize(N+1);

        // local variable to calculate sigma (divisor function)
        // i = pj^k * ..., and pi(i) = (1 + pj + pj^2 + ...)

        isPrime[0] = isPrime[1] = false;
        f[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                f[i] = MOD + 1 - i;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    f[t] = f[i];
                    break;
                } else {
                    f[t] = (1LL * f[primes[j]] * f [i]) % MOD;
                }
            }
        }
        for (int i = 1; i <= N; i++) {
            f[i] = add(f[i-1], mul(f[i], i));
        }
    }
};


int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    EulerSieve sieve(n);
    vector<int> s(m+1);
    for (int i = 1; i <= m; i++) s[i] = add(s[i-1], i);
    int ans = 0;
    for (int i = 1, j; i <= n; i=j+1) {
        j = min(n/(n/i), m/(m/i));
        int s_prod = mul(s[n/i], s[m/i]);
        int ps = sub(sieve.f[j], sieve.f[i-1]);
        int term = mul(ps, s_prod);
        ans = add(ans, term);
    }
    printf("%d\n", ans);
    return 0;
}
