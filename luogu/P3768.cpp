// https://www.luogu.org/problemnew/show/P3768
// 简单的数学题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e6+10;
int64_t P;
int64_t S[MAXN];
int64_t inv6;
int64_t pn;
map<int64_t, int64_t> s_map;

int64_t qpow(int64_t x, int64_t n) {
    int64_t ret = 1;
    while (n) {
        if (n&1) ret = (ret * x) % P;
        x = (x * x) % P;
        n >>= 1;
    }
    return ret;
}

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

        for (int i = 1; i <= N; i++) {
            S[i] = (1LL*i*i%P*phi[i]%P + S[i-1])%P;
        }
    }
};

int64_t s3(int64_t k) {
    k %= P;
    return (k*(k+1)/2) % P * ((k*(k+1)/2%P)) % P;
}

int64_t s2(int64_t k) {
    k %= P;
    return k*(k+1)%P * (k*2+1) % P * inv6 % P;
}

int64_t du(int64_t k) {
    if (k <= pn) return S[k];
    if (s_map.find(k) != s_map.end()) return s_map[k];
    int64_t res = s3(k), pre = 1, cur;
    for (int64_t i = 2, j; i <= k; i=j+1) {
        j = k/(k/i);
        cur = s2(j);
        res = (res - du(k/i)*(cur-pre)%P) % P;
        pre = cur;
    }
    return s_map[k] = (res+P) % P;
}

int64_t solve(int64_t n) {
    int64_t res = 0, pre = 0, cur;
    for (int64_t i = 1, j; i <= n; i=j+1) {
        j = n/(n/i);
        cur = du(j);
        res = (res + (s3(n/i)*(cur-pre))%P)%P;
        pre = cur;
    }
    return (res + P) % P;
}

int main() {
    int64_t n;
    scanf("%ld%ld", &P, &n);
    inv6 = qpow(6, P-2);
    pn = (int64_t)pow(n, 2.0/3);
    EulerSieve sieve(pn);
    printf("%ld", solve(n));
    return 0;
}
