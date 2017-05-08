// https://www.luogu.org/problem/show?pid=1857
// 质数取石子

#include <bits/stdc++.h>
using namespace std;


class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, mu, phi;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        mu.resize(N+1);
        phi.resize(N+1);

        isPrime[0] = isPrime[1] = false;
        mu[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    mu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    break;
                } else {
                    mu[t] = -mu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                }
            }
        }
    }
};

using PII = pair<int, int>;
const int MAXN = 20000;
int dp[MAXN+1];
int type[MAXN+1];

int main() {
    EulerSieve es(MAXN);
    dp[0] = dp[1] = 0;
    type[0] = type[1] = 0;
    for (int i = 0; i <= MAXN; i++) {
        for (int p: es.primes) {
            if (i + p > MAXN) break;
            if (type[i] == 0) {
                if (type[i+p] == 0) {
                    type[i+p] = 1;
                    dp[i+p] = dp[i]+1;
                } else {
                    dp[i+p] = min(dp[i+p], dp[i]+1);
                }
            } else {
                if (type[i+p] == 0) {
                    dp[i+p] = max(dp[i+p], dp[i]+1);
                }
            }
        }
    }

    int nt;
    scanf("%d", &nt);
    while (nt--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", type[n] ? dp[n] : -1);
    }

    return 0;
}
