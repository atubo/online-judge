// https://www.luogu.org/problemnew/show/P3455
// [POI2007]ZAP-Queries

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

const int MAXN = 50000;
int N;
int ps[MAXN+1];

int64_t solve(const EulerSieve &sieve, int a, int b, int d) {
    a = a / d;
    b = b / d;
    if (a > b) swap(a, b);
    int64_t ans = 0;
    for (int i = 1, j; i <= a; i = j+1) {
        j = min(a/(a/i), b/(b/i));
        ans += 1LL * (ps[j]-ps[i-1]) * (a/i) * (b/i);
    }
    return ans;
}

int main() {
    EulerSieve sieve(MAXN);
    for (int i = 1; i <= MAXN; i++) ps[i] = ps[i-1] + sieve.mu[i];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        printf("%ld\n", solve(sieve, a, b, d));
    }

    return 0;
}
