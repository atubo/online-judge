// https://www.luogu.org/problemnew/show/P1072
// Hankson 的趣味题

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

int T;
int A0, A1, B0, B1;

int main() {
    EulerSieve sieve(45000);
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &A0, &A1, &B0, &B1);
        if (B1 % A1 != 0) {
            printf("0\n");
            continue;
        }
        int k1 = A0/A1;
        int k2 = B1/B0;
        int k = B1/A1;
        int64_t ans = 1;
        for (int i = 0; i < (int)sieve.primes.size(); i++) {
            int64_t p = sieve.primes[i];
            if (p*p > k) break;
            int cnt = 0;
            while (k % p == 0) {
                if (k1 % p == 0 && k2 % p == 0) {
                    ans = 0;
                    break;
                }
                if (k1 % p != 0 && k2 % p != 0) {
                    cnt++;
                }
                k /= p;
            }
            if (ans == 0) break;
            ans *= (cnt+1);
        }
        if (k > 1) {
            int cnt = 0;
            if (k1 % k == 0 && k2 % k == 0) {
                ans = 0;
            }
            if (k1 % k != 0 && k2 % k != 0) {
                cnt++;
            }
            ans *= (cnt+1);
        }
        printf("%ld\n", ans);
    }

    return 0;
}
