// https://www.luogu.org/problemnew/show/P2508
// [HAOI2008]圆上的整点

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

EulerSieve euler(45000);

int solve(int n) {
    while (n > 0 && (n&1) == 0) n >>= 1;
    if (n == 0) return 4;
    int ret = 1;
    for (int p: euler.primes) {
        if (p == 2) continue;
        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            cnt++;
        }
        if (p % 4 == 1) {
            ret *= (2*cnt + 1);
        }
    }
    if (n > 1 && (n % 4 == 1)) {
        ret *= 3;
    }
    return ret * 4;
}

int main() {
    int n;
    cin >> n;
    int ans = solve(n);
    printf("%d\n", ans);
    return 0;
}
