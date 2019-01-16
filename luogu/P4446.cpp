// https://www.luogu.org/problemnew/show/P4446
// [AHOI2018初中组]根式化简

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, mu, phi, sigma;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        mu.resize(N+1);
        phi.resize(N+1);
        sigma.resize(N+1);

        // local variable to calculate sigma (divisor function)
        // i = pj^k * ..., and pi(i) = (1 + pj + pj^2 + ...)
        vector<int> pi(N+1);

        isPrime[0] = isPrime[1] = false;
        mu[1] = 1;
        phi[1] = 1;
        sigma[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
                sigma[i] = pi[i] = i + 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    mu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    pi[t] = pi[i] * primes[j] + 1;
                    sigma[t] = sigma[i]/pi[i] * pi[t];
                    break;
                } else {
                    mu[t] = -mu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                    pi[t] = primes[j] + 1;
                    sigma[t] = sigma[primes[j]] * sigma[i];
                }
            }
        }
    }
};

int N;

int64_t qroot(int64_t n) {
    double x = pow(n, 0.33333333);
    int64_t xi = x + 0.5;
    if (xi*xi*xi == n) return xi;
    return 1;
}

int64_t solve(int64_t x, const vector<int> &primes) {
    int64_t ans = 1;
    for (int p: primes) {
        int64_t pc = 1LL*p*p*p;
        while (x % pc == 0) {
            ans *= p;
            x /= pc;
        }
        while (x % p == 0) x /= p;
    }
    ans *= qroot(x);
    return ans;
}

int main() {
    EulerSieve sieve(32000);

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int64_t x;
        scanf("%ld", &x);
        int64_t ans = solve(x, sieve.primes);
        printf("%ld\n", ans);
    }

    return 0;
}
